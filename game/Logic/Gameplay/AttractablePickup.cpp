//
// Created by god on 16.12.2022.
//

#include "AttractablePickup.h"
#include "GameplaySceneManager.h"
#include "punity/Utils/PMath.h"
#include "game/Assets/strings.h"

namespace Game {
    void AttractablePickup::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        if (player == nullptr) {
            player = Punity::Engine.find_entity(Game::Names::PLAYER);
        }

        if (is_approaching_player) {
            // Set position of pickup to lerped value
            get_entity()->get_transform()->set_global(
                Punity::Utils::lerp(
                get_entity()->get_transform()->global_position,
                player->get_transform()->global_position,
                (Punity::Time.time - time_of_approaching_start) / INTERPOLATION_TIME
                )
            );

            return;
        }

        float distance_between_player_and_entity = Punity::Utils::distance(
                player->get_transform()->global_position,
                get_entity()->get_transform()->global_position
                );

        if (distance_between_player_and_entity < APPROACHING_DISTANCE) {
            // Start approaching the player_normal
            is_approaching_player = true;
            time_of_approaching_start = Punity::Time.time;
        }
    }
} // Game