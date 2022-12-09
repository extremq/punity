//
// Created by god on 08.12.2022.
//

#ifndef _PLAYERBEHAVIOUR_H
#define _PLAYERBEHAVIOUR_H

#include "punity/Punity.h"

namespace Game {
    class PlayerBehaviour : public Punity::Components::PComponent {
    private:
        bool m_is_alive = true;
        bool m_has_touched_chest = false;

        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;

        void compute_movement();
        void reset_status();
    public:
        bool is_alive();
        bool has_touched_chest();
    };
} // Game

#endif //_PLAYERBEHAVIOUR_H
