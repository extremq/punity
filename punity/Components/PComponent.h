//
// Created by god on 14.11.2022.
//

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <cstdint>
#include "punity/Entity/PEntity.fwd.h"

namespace Punity::Components {
    class PCollider; // Small forward iteration for pointer

    // The base component
    class PComponent {
    protected:
        // This state is individual and is not linked to parent Entity,
        // however updates wont be executed if parent entity is disabled.
        bool m_is_active = true;

        // Befriend class for access
        // Entity should have full control
        // over component.
        // Entities are not public to users
        friend class Punity::PEntity;

        static uint64_t component_count;
        uint64_t m_id = component_count++; // Increment id's

        // Parent entity of this component
        Punity::PEntity* m_parent_entity = nullptr;

        // Activated by set_active(true/false)
        // Also activated by parent entity, but only
        // when component itself is active.
        virtual void on_enable();
        virtual void on_disable();

        virtual void on_start_collision(PCollider*);
        virtual void on_collision(PCollider*);
        virtual void on_end_collision(PCollider*);

        virtual void on_update();
        virtual void on_destroy();
        virtual void on_start();

        // No need to move components.
        void set_parent(Punity::PEntity* parent);
    public:
        PComponent() = default;
        // Public read-only
        Punity::PEntity* get_entity();
        void set_active(bool);

        uint64_t get_id();

        bool is_active();
    };
} // Punity

#endif //_COMPONENT_H
