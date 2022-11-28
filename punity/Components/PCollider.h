//
// Created by god on 26.11.2022.
//

#ifndef _PCOLLIDER_H
#define _PCOLLIDER_H

#include "PComponent.h"
#include <queue>

namespace Punity::Components {
    enum Shape {BOX, CIRCLE};
    // Class for colliding template
    class PCollider : public PComponent {
    protected:
        Shape m_shape = BOX;
    public:
        uint8_t layer = 0;
        // static = doesn't move
        bool is_static = true;

        // trigger = only acts as a boundary
        bool is_trigger = false;

        virtual bool solve_collision(PCollider* other) { return false; }
        Shape get_shape() { return m_shape; }
    };

} // Components

#endif //_PCOLLIDER_H
