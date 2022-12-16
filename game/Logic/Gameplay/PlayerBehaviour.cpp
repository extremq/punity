//
// Created by god on 08.12.2022.
//

#include "PlayerBehaviour.h"
#include "punity/Components/PCollider.h"
#include "ActorBehaviour.h"
#include "GameplayPrefabCreator.h"
#include "game/Assets/colliders.h"
#include "GameplaySceneManager.h"
#include "game/Assets/colliders.h"
#include "punity/Utils/PCollisionComputation.h" // for dist
#include "Weapon.h"

namespace Game {

    bool PlayerBehaviour::has_touched_chest() {
        return m_has_touched_chest;
    }

    void PlayerBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        if (GameplaySceneManager::chest_loaded && other->get_entity()->get_name() == "Chest") {
            m_has_touched_chest = true;
            return;
        }
        // If its a heart or energy pickup, destroy them
        if(other->information == Colliders::COLLIDER_ENERGY_PICKUP || other->information == Colliders::COLLIDER_HEART_PICKUP) {

            if (other->information == Colliders::COLLIDER_ENERGY_PICKUP)
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
            case Colliders::COLLIDER_ENEMY_PROJECTILE_1:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(1);
                break;
            case Colliders::COLLIDER_ENEMY_PROJECTILE_2:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(2);
                break;
            case Colliders::COLLIDER_ENEMY_PROJECTILE_3:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(3);
                break;
            default:
                break;
        }
    }

    void PlayerBehaviour::fully_reset_player() {
        // Replace weapon
        change_weapon(Weapons::starting_weapon);
        m_is_using_starting_weapon = true;
        equipped_weapon = Weapons::empty_weapon;
        m_has_picked_up_any_weapon = false;

        // Restore energy
        remaining_energy = 99;

        // Reset touching status
        m_has_touched_chest = false;
    }

    void PlayerBehaviour::on_enable() {
        reset_status_for_new_stage();
    }

    void PlayerBehaviour::reset_status_for_new_stage() {
        room = Punity::Engine.find_entity("Room");
        enemies = Punity::Engine.find_entity("Enemies");

        // Store weapon component
        weapon_component = get_entity()->get_component<Weapon>();

        // Reset chest touch
        m_has_touched_chest = false;

        // Place player back
        get_entity()->get_transform()->set_global({0, -40});
    }

    void PlayerBehaviour::on_update() {
        compute_movement();

        // Wait for enemies to be loaded!
        if (!GameplaySceneManager::enemies_loaded) return;

        // Get nearest enemy
        Punity::Utils::PVector nearest_enemy = compute_nearest_enemy();

        // TODO Pick up weapon
        // Switching weapons
        if (m_has_picked_up_any_weapon && Punity::Button.read_button(JOY_BTN)) {
            // Switch between starting weapon and equipped weapon
            if (m_is_using_starting_weapon) {
                m_is_using_starting_weapon = false;
                change_weapon(equipped_weapon);
            }
            else {
                m_is_using_starting_weapon = true;
                change_weapon(Weapons::starting_weapon);
            }
        }

        // Shoot test!
        if (Punity::Button.read_button(ACTION_BTN)) {
            // You need enough bullets to be able to shoot
            // However starting weapon uses no ammo, just magic
            if (!m_is_using_starting_weapon && remaining_energy - weapon_component->get_bullet_count() < 0) return;


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

        // Translate the player
        get_entity()->get_transform()->translate(joystick_direction * Punity::Time.delta_time * 30);
    }

    Punity::Utils::PVector PlayerBehaviour::compute_nearest_enemy() {
        Punity::Utils::PVector player_pos = get_entity()->get_transform()->global_position, nearest_enemy;

        // Loop through children of Enemies and get their position. Choose the nearest.
        float min_distance = 999.0f, distance;
        uint64_t chosen_id = 0;
        for (auto enemy : enemies->get_children()) {
            distance = Punity::Collision::distance(player_pos, enemy->get_transform()->global_position);

            if (min_distance > distance) {
                nearest_enemy = enemy->get_transform()->global_position;
                min_distance = distance;
                chosen_id = enemy->get_id();
            }
        }

        // Show selector above
        for (auto enemy : enemies->get_children()) {
            if (enemy->get_id() != chosen_id) {
                enemy->get_child_by_name("Selector")->set_active(false);
            }
            else {
                enemy->get_child_by_name("Selector")->set_active(true);
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

} // Game