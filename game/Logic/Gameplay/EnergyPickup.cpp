//
// Created by god on 16.12.2022.
//

#include "EnergyPickup.h"
#include "GameplaySceneManager.h"
#include "punity/Utils/PCollisionComputation.h"

namespace Game {


    Punity::Utils::PVector lerp(Punity::Utils::PVector a, Punity::Utils::PVector b, float t)
    {
        Punity::Utils::PVector interpolated;
        // Simple LERP function
        interpolated.x = a.x * (1.0f - t) + (b.x * t);
        interpolated.y = a.y * (1.0f - t) + (b.y * t);

        return interpolated;
    }

    void EnergyPickup::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        if (player == nullptr) {
            player = Punity::Engine.find_entity("Player");
        }

        if (is_approaching_player) {
            // Set position of energy to lerped value
            get_entity()->get_transform()->set_global(
                lerp(
                get_entity()->get_transform()->global_position,
                player->get_transform()->global_position,
                (Punity::Time.time - time_of_approaching_start) / INTERPOLATION_TIME
                )
            );

            return;
        }

        float distance_between_player_and_entity = Punity::Collision::distance(
                player->get_transform()->global_position,
                get_entity()->get_transform()->global_position
                );

        if (distance_between_player_and_entity < APPROACHING_DISTANCE) {
            // Start approaching the player
            is_approaching_player = true;
            time_of_approaching_start = Punity::Time.time;
        }
    }
} // Game