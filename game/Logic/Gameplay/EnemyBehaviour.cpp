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
#include "game/Assets/strings.h"
#include "punity/Utils/PInvokable.h"
#include "RoomBehaviour.h"

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

    void EnemyBehaviour::move() {
        if (Punity::Time.time > next_move) {
            // Choose a random moving time
            move_time = Punity::Utils::random(0.75f, 1);
            float stand_time = Punity::Utils::random(0, 0.33f);
            next_move = Punity::Time.time + move_time + stand_time;

            // Start moving
            new Punity::Utils::PInvokable<EnemyBehaviour>(
                    &EnemyBehaviour::translate_to_random_valid_place,
                    this,
                    stand_time,
                    get_entity()->get_id()
                    );
        }
    }

    void EnemyBehaviour::translate_to_random_valid_place() {
        Punity::Utils::PVector directions[4] = {
                {0, 8},
                {8, 0},
                {0, -8},
                {-8, 0}
        };

        int pick = std::floor(Punity::Utils::random(0, 3.99f));
        Punity::Utils::PVector target = get_entity()->get_transform()->global_position + directions[pick];

        while(room->get_component<RoomBehaviour>()->tiles[static_cast<int>((64.0f + target.y) / 8.0f)][static_cast<int>((64.0f + target.x) / 8.0f)] != EMPTY) {
            // Reroll until empty tile
            pick = std::floor(Punity::Utils::random(0, 3.99f));
            target = get_entity()->get_transform()->global_position + directions[pick];
        }

        get_entity()->get_component<MovingBehaviour>()->translate_to(
                target,
                move_time
                );
    }

    void EnemyBehaviour::shoot() {
        if (Punity::Time.time < shooting_start) {
            shooting_is_paused = true;
            return;
        }
        else {
            if (shooting_is_paused) {
                shooting_is_paused = false;
                shooting_end = Punity::Time.time + shoot_time;
            }
        }

        if (Punity::Time.time < shooting_end) {
            // Attempt shooting
            get_entity()->get_component<Weapon>()->shoot(
                    get_entity()->get_transform()->global_position,
                    player->get_transform()->global_position,
                    room,
                    false
            );
        }
        else {
            shooting_start = Punity::Time.time + pause_time;
        }
    }

    void EnemyBehaviour::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        move();
        shoot();
    }

    void EnemyBehaviour::on_enable() {
        player = Punity::Engine.find_entity(Game::Names::PLAYER);
        room = Punity::Engine.find_entity(Game::Names::ROOM);

        // Set a random offset.
        pause_time = Punity::Utils::random(1.0f, 1.5f);
        shooting_start = Punity::Time.time + Punity::Utils::random() + pause_time;
        shoot_time = Punity::Utils::random(3, 4);
        next_move = Punity::Time.time + Punity::Utils::random(0.33f, 0.66f);
    }

    void EnemyBehaviour::on_destroy() {
        if (!room->is_globally_active()) return;

        // Determine rewards for player_normal
        determine_drop();
    }

    void EnemyBehaviour::determine_drop() {
        // Create a random amount of energy pickups (count from 0 to 1)
        uint8_t random_amount = std::lround(Punity::Utils::random(0.0f, 1.0f));

        // If we happen to not generate any energy pickup, see if you can make a heart pickup
        if (random_amount == 0)
        {
            // Also roll a number to check for hearts
            if (Punity::Utils::random() < 0.50f)
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