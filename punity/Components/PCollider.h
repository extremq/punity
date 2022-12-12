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

        // Each derived class will solve its own collision in its own way
        virtual bool solve_collision(PCollider* other) { return false; }

        // m_colliders functions made for checking when an intersection
        // begins or ends
        PCollider* check_if_exists_as_collider(PCollider* other);
        void delete_collider(PCollider* other);
        void add_collider(PCollider* other);

        // Shape for easy type detection
        Shape m_shape = BOX;

        // Needed for cleaning up
        void on_disable() override;
        void on_destroy() override;
    public:
        // static = doesn't move
        bool is_static = true;

        // trigger = only acts as a boundary
        bool is_trigger = false;

        // Information.
        uint8_t information = 0;

        // Chain-calling
        PCollider* set_static(bool _static);
        PCollider* set_trigger(bool _trigger);
        PCollider* set_information(uint8_t _information);

        Shape get_shape() { return m_shape; }
    };

} // Components

#endif //_PCOLLIDER_H
