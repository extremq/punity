//
// Created by god on 08.12.2022.
//

#include "PlayerBehaviour.h"
#include "punity/Components/PCollider.h"
#include "ActorBehaviour.h"
#include "GameplayPrefabCreator.h"
#include "game/Assets/colliders.h"
#include "GameplaySceneManager.h"
#include "punity/Utils/PMath.h"
#include "Weapon.h"
#include "WeaponPickup.h"
#include "game/Assets/strings.h"
#include "RoomBehaviour.h"

namespace Game {

    bool PlayerBehaviour::has_touched_chest() {
        return touched_chest;
    }

    void PlayerBehaviour::on_collision(Punity::Components::PCollider *other) {
        if (other->information == Colliders::WEAPON_PICKUP) {
            weapon_collided_with = other;
        }
        else
            weapon_collided_with = nullptr;
    }

    void PlayerBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        if (GameplaySceneManager::chest_loaded && other->get_entity()->get_name() == Game::Names::CHEST) {
            touched_chest = true;
            return;
        }

        // If its a heart or energy pickup, destroy them
        if(other->information == Colliders::ENERGY_PICKUP || other->information == Colliders::HEART_PICKUP) {

            if (other->information == Colliders::ENERGY_PICKUP)
                // Add energy and cap it to 99
                remaining_energy = std::min(99, remaining_energy + 3);
            else
                // Add one hitpoint
                get_entity()->get_component<ActorBehaviour>()->add_hitpoints(1);

            // Destroy the pickup
            other->get_entity()->destroy();

            // Early exit to be safe
            return;
        }

        // Subtract hitpoints
        compute_damage_dealt_by_projectile(other->information);
    }

    void PlayerBehaviour::compute_damage_dealt_by_projectile(uint8_t projectile_type) {
        switch (projectile_type) {
            case Colliders::ENEMY_PROJECTILE_1:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(1);
                break;
            case Colliders::ENEMY_PROJECTILE_2:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(2);
                break;
            case Colliders::ENEMY_PROJECTILE_3:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(3);
                break;
            default:
                break;
        }
    }

    void PlayerBehaviour::fully_reset_player() {
        // Replace weapon
        change_weapon(Weapons::starting_weapon);
        using_starting_weapon = true;
        equipped_weapon = Weapons::empty_weapon;
        picked_up_any_weapon = false;

        // Restore energy
        remaining_energy = 99;

        // Reset touching status
        touched_chest = false;
    }

    void PlayerBehaviour::on_enable() {
        reset_status_for_new_stage();
    }

    void PlayerBehaviour::reset_status_for_new_stage() {
        room = Punity::Engine.find_entity(Game::Names::ROOM);
        enemies = Punity::Engine.find_entity(Game::Names::ENEMIES);

        // Store weapon component
        weapon_component = get_entity()->get_component<Weapon>();

        // Reset chest touch
        touched_chest = false;

        // Place player back
        get_entity()->get_transform()->set_global({0, -40});
    }

    void PlayerBehaviour::on_update() {
        compute_movement();

        Punity::Utils::PVector nearest_enemy = compute_nearest_enemy();

        if (Punity::Time.time - last_joystick_click_time > 0.25f &&
                Punity::Button.read_button(JOY_BTN)) {

            // If picked up a weapon
            if (weapon_collided_with != nullptr) {

                last_joystick_click_time = Punity::Time.time;
                // Touching a weapon pickup and clicked on pick-up!
                equipped_weapon = weapon_collided_with->get_entity()->get_component<WeaponPickup>()->swap_weapon(equipped_weapon);

                // Also change to new weapon
                using_starting_weapon = false;
                change_weapon(equipped_weapon);

                if (!picked_up_any_weapon) {
                    // Since it's our first weapon, we should not be able to swap it
                    weapon_collided_with->get_entity()->destroy();
                }

                picked_up_any_weapon = true;
            }

            // Switching weapons
            // Also have a cooldown on clicks
            else if (picked_up_any_weapon) {
                last_joystick_click_time = Punity::Time.time;
                // Switch between starting weapon and equipped weapon
                if (using_starting_weapon) {
                    using_starting_weapon = false;
                    change_weapon(equipped_weapon);
                }
                else {
                    using_starting_weapon = true;
                    change_weapon(Weapons::starting_weapon);
                }
            }
        }

        // Shoot test!
        if (Punity::Button.read_button(ACTION_BTN)) {
            // You need enough energy to be able to shoot
            // However starting weapon uses no energy, just magic
            if (!using_starting_weapon && remaining_energy - weapon_component->get_energy_cost() < 0) return;

            // If we actually shoot and aren't on cooldown
            if (weapon_component->shoot(
                    get_entity()->get_transform()->global_position,
                    nearest_enemy,
                    room,
                    true
                    )) {
                // Subtract energy and shoot
                remaining_energy -= weapon_component->get_energy_cost();
            }
        }
    }

    void PlayerBehaviour::compute_movement() {
        // Construct vector of direction
        auto joystick_direction = Punity::Utils::PVector();
        joystick_direction.x = Punity::Joystick.get_x_direction();
        joystick_direction.y = Punity::Joystick.get_y_direction();

        // Normalize the vector
        joystick_direction = joystick_direction.norm();

        // Save the last direction
        last_joystick_direction = joystick_direction;

        // Translate the player
        get_entity()->get_transform()->translate(joystick_direction * Punity::Time.delta_time * 30);
    }

    bool PlayerBehaviour::check_if_player_can_hit_enemy(Punity::Utils::PVector enemy_pos) {
        auto& tiles = room->get_component<RoomBehaviour>()->tiles;

        auto player_pos = get_entity()->get_transform()->global_position;

        // Normalize everything
        Punity::Utils::PVector shifted_player = player_pos;
        shifted_player += {64.0f, 64.0f};
        Punity::Utils::PVector shifted_enemy = enemy_pos;
        shifted_enemy += {64.0f, 64.0f};

        // Get row and column of player and enemy for optimisations
        int row_player = std::floor(shifted_player.y / 8.0f);
        int column_player = std::floor(shifted_player.x / 8.0f);

        int row_enemy = std::floor(shifted_enemy.y / 8.0f);
        int column_enemy = std::floor(shifted_enemy.x / 8.0f);

        // Compute the line between player and enemy
        float slope, extra;
        bool is_vertical = false;
        bool is_horizontal = false;
        if (std::abs(shifted_enemy.y - shifted_player.y) < 0.001f) {
            is_vertical = true;
        }
        else if (std::abs(shifted_enemy.x - shifted_player.x) < 0.001f) {
            is_horizontal = true;
        }
        else {
            slope = (shifted_enemy.y - shifted_player.y) / (shifted_enemy.x - shifted_player.x);
            extra = shifted_player.y - slope * shifted_player.x;
        }

        for (int row = std::min(row_player, row_enemy); row <= std::max(row_player, row_enemy); ++row) {
            for (int column = std::min(column_player, column_enemy); column <= std::max(column_player, column_enemy); ++column) {
                // Ignore anything else other than walls
                // Ignore tiles of player and enemy
                if (tiles[row][column] != WALL) continue;

                // If this is vertical, we are traversing a line starting from player to enemy.
                // Encountering a wall means no way of hitting.
                if (is_vertical || is_horizontal) return false;

                Punity::Utils::PVector center_of_wall = {column * 8.0f + 4.0f, row * 8.0f + 4.0f};

                // Check the two vertical sidees for intersection
                float y1 = slope * (center_of_wall.x - 4.0f) + extra;
                float y2 = slope * (center_of_wall.x + 4.0f) + extra;


                if (y1 > center_of_wall.y - 4.0f && y1 < center_of_wall.y + 4.0f) {
                    return false;
                }
                if (y2 > center_of_wall.y - 4.0f && y2 < center_of_wall.y + 4.0f) {
                    return false;
                }
                // Check the two horizontal sides for intersection
                float x1 = (center_of_wall.y - 4.0f - extra) / slope;
                float x2 = (center_of_wall.y + 4.0f - extra) / slope;

                if (x1 > center_of_wall.x - 4.0f && x1 < center_of_wall.x + 4.0f) {
                    return false;
                }
                if (x2 > center_of_wall.x - 4.0f && x2 < center_of_wall.x + 4.0f) {
                    return false;
                }
            }
        }

        return true;
    }

    Punity::Utils::PVector PlayerBehaviour::compute_nearest_enemy() {
        Punity::Utils::PVector player_pos = get_entity()->get_transform()->global_position, nearest_enemy;

        // In case there are no enemies, default to shooting in the last direction
        nearest_enemy = player_pos + last_joystick_direction;

        // Loop through children of Enemies and get their position. Choose the nearest.
        float min_distance = 999.0f, distance;
        uint64_t chosen_id = 0;
        for (auto enemy : enemies->get_children()) {
            if (!check_if_player_can_hit_enemy(enemy->get_transform()->global_position)) continue;

            distance = Punity::Utils::distance(player_pos, enemy->get_transform()->global_position);
            if (min_distance > distance) {
                nearest_enemy = enemy->get_transform()->global_position;
                min_distance = distance;
                chosen_id = enemy->get_id();
            }
        }

        // Show selector above
        for (auto enemy : enemies->get_children()) {
            if (enemy->get_id() != chosen_id) {
                enemy->get_child_by_name(Game::Names::SELECTOR)->set_active(false);
            }
            else {
                enemy->get_child_by_name(Game::Names::SELECTOR)->set_active(true);
            }
        }

        return nearest_enemy;
    }

    void PlayerBehaviour::change_weapon(Weapons::WeaponConfig weaponConfig) {
        weapon_component->set_weapon(weaponConfig);
    }

    int16_t PlayerBehaviour::get_remaining_energy() {
        return remaining_energy;
    }

    bool PlayerBehaviour::is_using_starting_weapon() {
        return using_starting_weapon;
    }

    bool PlayerBehaviour::has_picked_up_any_weapon() {
        return picked_up_any_weapon;
    }

    Weapons::WeaponConfig PlayerBehaviour::get_equipped_weapon() {
        return equipped_weapon;
    }

} // Game