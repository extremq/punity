//
// Created by god on 22.12.2022.
//

#include "CrateBehaviour.h"
#include "punity/Components/PCollider.h"
#include "game/Assets/colliders.h"
#include "GameplayPrefabCreator.h"

namespace Game {
    void CrateBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        // If hit by player or projectile, destroy itself
        if (other->information == Game::Colliders::PLAYER ||
                (other->information >= Game::Colliders::PLAYER_PROJECTILE_1 && other->information <= Game::Colliders::ENEMY_PROJECTILE_4) ) {
            // Create some energy pickups and set them to Room
            if (Punity::Utils::random() < 0.5f)
                GameplayPrefabCreator::drop_energy_pickups(get_entity()->get_parent(), 2, get_entity()->get_transform()->global_position);

            get_entity()->destroy();
        }
    }
} // Game