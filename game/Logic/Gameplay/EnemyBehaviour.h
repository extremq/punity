//
// Created by god on 12.12.2022.
//

#ifndef _ENEMYBEHAVIOUR_H
#define _ENEMYBEHAVIOUR_H

#include "game/Logic/SceneManager.h"
#include "MovingBehaviour.h"

namespace Game {

    class EnemyBehaviour : public Punity::Components::PComponent {
        Punity::PEntity* player = nullptr;
        Punity::PEntity* room = nullptr;

        float shooting_start = 0.0f;
        float shooting_end = 0.0f;
        float shoot_time = 0.0f;
        float pause_time = 0.0f;
        bool shooting_is_paused = true;

        float next_move = 0.0f;
        float move_time = 0.0f;

        void compute_damage_dealt_by_projectile(uint8_t projectile_type);
        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;
        void on_destroy() override;

        // Death drops
        void determine_drop();

        void move();

        void shoot();

        void translate_to_random_valid_place();
    };

} // Game

#endif //_ENEMYBEHAVIOUR_H
