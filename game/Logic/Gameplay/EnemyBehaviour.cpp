//
// Created by god on 12.12.2022.
//

#include "EnemyBehaviour.h"
#include "punity/Components/PCollider.h"
#include "GameplayPrefabCreator.h"
#include "game/Assets/colliders.h"
#include "ActorBehaviour.h"
#include "GameplaySceneManager.h"
#include "Weapon.h"

namespace Game {
    void EnemyBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        compute_damage_dealt_by_projectile(other->information);
    }

    void EnemyBehaviour::compute_damage_dealt_by_projectile(uint8_t projectile_type) {
        // Get projectile type and subtract hitpoints based on that
        switch(projectile_type) {
            case Game::Colliders::PLAYER_PROJECTILE_1:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(1);
                break;
            case Game::Colliders::PLAYER_PROJECTILE_2:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(2);
                break;
            case Game::Colliders::PLAYER_PROJECTILE_3:
                get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(3);
                break;
            default:
                break;
        }
    }

    void EnemyBehaviour::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        // Attempt shooting each time you can
        get_entity()->get_component<Weapon>()->shoot(
                get_entity()->get_transform()->global_position,
                player->get_transform()->global_position,
                room,
                false
        );
    }

    void EnemyBehaviour::on_enable() {
        player = Punity::Engine.find_entity("Player");
        room = Punity::Engine.find_entity("Room");
    }

    void EnemyBehaviour::on_destroy() {
        if (!room->is_globally_active()) return;

        // Determine rewards for player
        determine_drop();
    }

    void EnemyBehaviour::determine_drop() {
        // Create a random amount of energy pickups (count from 0 to 1)
        uint8_t random_amount = std::round(Punity::Utils::random(0.0f, 1.0f));

        // If we happen to not generate any energy pickup, see if you can make a heart pickup
        if (random_amount == 0)
        {
            // Also roll a number to check for hearts
            if (Punity::Utils::random() < 0.20f)
                GameplayPrefabCreator::drop_heart_pickups(room,
                                                          1,
                                                          get_entity()->get_transform()->global_position);
        }
        else
            GameplayPrefabCreator::drop_energy_pickups(room,
                                                      random_amount,
                                                      get_entity()->get_transform()->global_position);
    }
} // Game