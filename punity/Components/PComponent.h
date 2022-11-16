//
// Created by god on 14.11.2022.
//

#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <cstdint>
#include "punity/Entity/PEntity.fwd.h"

namespace Punity::Components {
    // The base component
    class PComponent {
    private:
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
        virtual void on_enable() {}
        virtual void on_disable() {}

        // Called when parent is enabled/disabled
        virtual void on_entity_enable() {}
        virtual void on_entity_disable() {}

        virtual void on_update() {}
        virtual void on_destroy() {}

        // No need to move components for no reason.
        void set_parent(Punity::PEntity* parent);
    public:
        // Public read-only
        Punity::PEntity *const & entity = m_parent_entity;
        void set_active(bool);

    };
} // Punity

#endif //_COMPONENT_H
