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
    class PCollider : PComponent {
    private:
        Shape m_shape = BOX;
    public:
        uint8_t layer = 0;
        // static = doesn't move
        bool is_static = true;

        // trigger = only acts as a boundary
        bool is_trigger = false;

        virtual void solve_collisions() {};
    };

} // Components

#endif //_PCOLLIDER_H
