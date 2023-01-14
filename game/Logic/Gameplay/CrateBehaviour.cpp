//
// Created by god on 22.12.2022.
//

#include "CrateBehaviour.h"
#include "punity/Components/PCollider.h"
#include "game/Assets/colliders.h"
#include "GameplayPrefabCreator.h"

namespace Game {
    void CrateBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        // If hit by player, enemy or projectile, destroy itself
        if (other->information == Game::Colliders::PLAYER ||
                (other->information >= Game::Colliders::PLAYER_PROJECTILE_1 && other->information <= Game::Colliders::ENEMY_PROJECTILE_4) ) {

            auto roll = Punity::Utils::random();

            // Create some energy pickups or shield and attach them to room
            if (roll < 0.5f)
                GameplayPrefabCreator::drop_energy_pickups(get_entity()->get_parent(), 3, get_entity()->get_transform()->global_position);
            else if (roll < 0.55f)
                GameplayPrefabCreator::drop_shield_pickups(get_entity()->get_parent(), 1, get_entity()->get_transform()->global_position);
            else if (roll < 0.60f)
                GameplayPrefabCreator::drop_heart_pickups(get_entity()->get_parent(), 2, get_entity()->get_transform()->global_position);

            get_entity()->destroy();
        }
    }
} // Game