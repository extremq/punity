//
// Created by god on 14.11.2022.
//

#ifndef _ENTITY_H
#define _ENTITY_H

#include "punity/Components/PComponent.fwd.h"
#include "punity/Components/PTransform.h"
#include "punity/Engine/PEngine.fwd.h"

#include <cstdint>
#include <string>
#include <list>
#include <memory>

namespace Punity {
    class PEntity {
    private:
        // Entity name
        std::string m_name;

        bool m_is_active = true;
        bool m_is_destroyed = false;

        // Befriend class for access
        friend class Punity::PEngine;

        static uint64_t entity_count;
        uint64_t m_id = entity_count++; // Increment id's

        // Entity transform
        Components::PTransform m_transform;

        // List of components
        std::list<Punity::Components::PComponent*> m_components;

        // Parent entity and children entities
        PEntity* m_parent_entity = nullptr;
        std::list<Punity::PEntity*> m_children_entities;

        void report_enable_to_components();
        void report_disable_to_components();
        void report_update_to_components();
        void report_destroy_to_components();

        PEntity &operator=(const PEntity &);
    public:
        void destroy();

        // Disable copy
        ~PEntity();
        PEntity();
        explicit PEntity(std::string const& new_name);

        // Public read-only
        Components::PTransform const& transform = m_transform;
        PEntity* const & parent_of_entity = m_parent_entity;

        std::string const& name = m_name;

        void set_name(std::string const& new_name);
        void set_active(bool);

        // Return all children entities
        std::list<PEntity*> const & get_children();

        PEntity* find_child_entity(PEntity* entity);

        void remove_child_entity(PEntity* entity);

        // Return components
        std::list<Punity::Components::PComponent*> const & get_all_components();

        Punity::Components::PComponent* find_component(Punity::Components::PComponent* component);

        // Add a new child entity
        void add_child(PEntity* entity);

        // Add a new component
        void add_component(Components::PComponent* component);

        void set_parent(PEntity* parent);
    };
}


#endif //_ENTITY_H
