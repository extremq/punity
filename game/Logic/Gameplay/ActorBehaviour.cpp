//
// Created by god on 12.12.2022.
//

#include "ActorBehaviour.h"

namespace Game {
    void ActorBehaviour::set_hitpoints(uint8_t hitpoints) {
        if (hitpoints > 0) m_is_dead = false;
        else m_is_dead = true;

        m_hitpoints = hitpoints;
    }

    uint8_t ActorBehaviour::get_hitpoints() {
        return m_hitpoints;
    }

    bool ActorBehaviour::is_dead() {
        return m_is_dead;
    }

    void ActorBehaviour::add_hitpoints(uint8_t hitpoints) {
        // Mind the overflow
        m_hitpoints = m_hitpoints > m_hitpoints + hitpoints ?
                255 : m_hitpoints + hitpoints;
    }

    void ActorBehaviour::subtract_hitpoints(uint8_t hitpoints) {
        // Mind the underflow
        m_hitpoints = m_hitpoints < m_hitpoints - hitpoints ?
                0 : m_hitpoints - hitpoints;

        // TODO fix this underflow check

        if (m_hitpoints == 0) {
            m_is_dead = true;
        }
    }
} // Game