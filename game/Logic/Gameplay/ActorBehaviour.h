//
// Created by god on 12.12.2022.
//

#ifndef _ACTORBEHAVIOUR_H
#define _ACTORBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {
    // Simple common behaviour for actors - players and enemies
    // Only job it has is to keep the hitpoints of the actor in check

    class ActorBehaviour : public Punity::Components::PComponent {
    private:
        int16_t m_hitpoints = 3;
        bool m_is_dead = false;
        int16_t m_max_hitpoints = 3;
    public:
        // TODO make max_health and replenish_health
        void set_hitpoints(int16_t hitpoints);
        void set_max_hitpoints(int16_t hitpoints);
        void replenish_hitpoints();
        int16_t  get_hitpoints();
        void add_hitpoints(int16_t hitpoints);
        void subtract_hitpoints(int16_t hitpoints);
        bool is_dead();
    };
} // Game

#endif //_ACTORBEHAVIOUR_H
