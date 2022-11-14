//
// Created by god on 14.11.2022.
//

#ifndef _ENTITY_H
#define _ENTITY_H

#include "punity/Components/PComponent.h"
#include "punity/Punity.h"

#include <cstdint>
#include <list>

namespace Punity {
    class PEntity {
    private:
        // Entity name
        // TODO make constructor
        std::string m_name = "";

        bool m_is_active = true;

        // Befriend class for access
        friend class Punity::PEngine;

        static uint64_t entity_count;
        uint64_t m_id = entity_count++; // Increment id's

        // List of components
        std::list<Punity::Components::PComponent*> m_components;

        // Parent entity and children entities
        PEntity* m_parent_entity = nullptr;
        std::list<PEntity*> m_children_entities;

        void on_enable() {};
        void on_disable() {};
        void propagate_update();
    public:
        // Public read-only
        std::string const& name = m_name;

        void set_name(std::string const& new_name);
        void set_active(bool);

        // Return all children entities
        std::list<Punity::PEntity*>& get_children();

        // Return components
        std::list<Punity::Components::PComponent*>& get_components();

        // Add a new child entity
        void add_child(PEntity* entity);

        // Add a new component
        void add_component(Components::PComponent* component);

        void set_parent(PEntity* parent);
    };
}


#endif //_ENTITY_H
