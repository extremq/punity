//
// Created by god on 12.12.2022.
//

#include "ActorBehaviour.h"

namespace Game {
    void ActorBehaviour::set_hitpoints(int16_t hitpoints) {
        if (hitpoints > m_max_hitpoints) hitpoints = m_max_hitpoints;

        if (hitpoints > 0) m_is_dead = false;
        else m_is_dead = true;

        m_hitpoints = hitpoints;
    }

    int16_t ActorBehaviour::get_hitpoints() {
        return m_hitpoints;
    }

    bool ActorBehaviour::is_dead() {
        return m_is_dead;
    }

    void ActorBehaviour::add_hitpoints(int16_t hitpoints) {
        // Checks with max_hitpoints
        m_hitpoints = m_hitpoints + hitpoints > m_max_hitpoints ?
                m_max_hitpoints : m_hitpoints + hitpoints;
    }

    void ActorBehaviour::subtract_hitpoints(int16_t hitpoints) {
        // Checks with 0
        m_hitpoints = m_hitpoints - hitpoints < 0 ?
                0 : m_hitpoints - hitpoints;

        if (m_hitpoints == 0) {
            m_is_dead = true;
        }
    }

    void ActorBehaviour::set_max_hitpoints(int16_t hitpoints) {
        m_max_hitpoints = hitpoints;
    }

    void ActorBehaviour::replenish_hitpoints() {
        // Replenishes the hitpoints of the actor fully
        m_hitpoints = m_max_hitpoints;
    }
} // Game