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

    Punity::Utils::PVector PlayerBehaviour::compute_nearest_enemy() {
        Punity::Utils::PVector player_pos = get_entity()->get_transform()->global_position, nearest_enemy;

        // In case there are no enemies, default to shooting in the last direction
        nearest_enemy = player_pos + last_joystick_direction;

        // Loop through children of Enemies and get their position. Choose the nearest.
        float min_distance = 999.0f, distance;
        uint64_t chosen_id = 0;
        for (auto enemy : enemies->get_children()) {
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