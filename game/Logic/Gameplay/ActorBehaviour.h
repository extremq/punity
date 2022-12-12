//
// Created by god on 12.12.2022.
//

#ifndef _ACTORBEHAVIOUR_H
#define _ACTORBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {
    class ActorBehaviour : public Punity::Components::PComponent {
    private:
        uint8_t m_hitpoints = 6;
        bool m_is_dead = false;
    public:
        void set_hitpoints(uint8_t hitpoints);
        uint8_t  get_hitpoints();
        void add_hitpoints(uint8_t hitpoints);
        void subtract_hitpoints(uint8_t hitpoints);

        bool is_dead();
    };
} // Game

#endif //_ACTORBEHAVIOUR_H
