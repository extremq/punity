//
// Created by god on 12.12.2022.
//

#include "EnemyBehaviour.h"
#include "punity/Components/PCollider.h"
#include "ActorBehaviour.h"
#include "GameplaySceneManager.h"
#include "Weapon.h"

namespace Game {
    void EnemyBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        if (other->information == COLLIDER_PLAYER_PROJECTILE) {
            // Subtract hitpoint
            get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(1);
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
} // Game