//
// Created by god on 26.11.2022.
//

#ifndef _PCOLLIDER_H
#define _PCOLLIDER_H

#include "PComponent.h"
#include "punity/Engine/PEngine.fwd.h"
#include <map>
#include <queue>

namespace Punity::Components {
    enum Shape {BOX, CIRCLE};
    // Class for colliding template
    class PCollider : public PComponent {
    private:
        std::map<uint64_t, PCollider*> m_colliders;
    protected:
        friend class Punity::PEngine;
        virtual bool solve_collision(PCollider* other) { return false; }

        PCollider* check_if_exists_as_collider(PCollider* other);
        void delete_collider(PCollider* other);
        void add_collider(PCollider* other);
        Shape m_shape = BOX;
    public:
        uint8_t layer = 0;
        // static = doesn't move
        bool is_static = true;

        // trigger = only acts as a boundary
        bool is_trigger = false;

        Shape get_shape() { return m_shape; }
    };

} // Components

#endif //_PCOLLIDER_H
