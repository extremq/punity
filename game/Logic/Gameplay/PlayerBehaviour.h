//
// Created by god on 08.12.2022.
//

#ifndef _PLAYERBEHAVIOUR_H
#define _PLAYERBEHAVIOUR_H

#include "punity/Punity.h"
#include "Weapon.h"

namespace Game {
    class PlayerBehaviour : public Punity::Components::PComponent {
    private:
        bool m_has_touched_chest = false;
        Punity::PEntity* enemies = nullptr;
        Punity::PEntity* room = nullptr;
        Weapon* weapon = nullptr;

        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;

        void compute_movement();
        void reset_status();

        Punity::Utils::PVector compute_nearest_enemy();
    public:
        bool has_touched_chest();
    };
} // Game

#endif //_PLAYERBEHAVIOUR_H
