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
        bool m_is_active = true;

        // Befriend class for access
        friend class Punity::PEntity;

        static uint64_t component_count;
        uint64_t m_id = component_count++; // Increment id's

        // Parent entity of this component
        Punity::PEntity* m_parent_entity = nullptr;

        // Activated by set_active(true/false)
        virtual void on_enable() {}
        virtual void on_disable() {}
        virtual void on_update() {}

        // No need to move components for no reason.
        void set_parent(Punity::PEntity* parent);
    public:
        // Public read-only
        Punity::PEntity *const & entity = m_parent_entity;
        void set_active(bool);
    };
} // Punity

#endif //_COMPONENT_H
