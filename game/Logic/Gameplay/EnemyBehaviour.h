//
// Created by god on 12.12.2022.
//

#ifndef _ENEMYBEHAVIOUR_H
#define _ENEMYBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {

    class EnemyBehaviour : public Punity::Components::PComponent {
        Punity::PEntity* player;
        Punity::PEntity* room;

        void compute_damage_dealt_by_projectile(uint8_t projectile_type);
        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;
    };

} // Game

#endif //_ENEMYBEHAVIOUR_H
