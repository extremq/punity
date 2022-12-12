//
// Created by god on 12.12.2022.
//

#include "EnemyBehaviour.h"
#include "punity/Components/PCollider.h"
#include "ActorBehaviour.h"

namespace Game {
    void EnemyBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        if (other->information == COLLIDER_PLAYER_PROJECTILE) {
            // Subtract hitpoint
            get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(1);
        }
    }
} // Game