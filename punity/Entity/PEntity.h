//
// Created by god on 14.11.2022.
//
#ifndef _ENTITY_H
#define _ENTITY_H
#include <typeinfo>

#include "punity/Components/PComponent.fwd.h"
#include "punity/Components/PTransform.h"
#include "punity/Engine/PEngine.fwd.h"

#include <cstdint>
#include <string>
#include <list>
#include <iostream>

namespace Punity {
    class PEntity {
    private:
        // Entity name
        std::string m_name;

        // Children entities
        std::list<Punity::PEntity*> m_children_entities;

        // List of components
        std::list<Punity::Components::PComponent*> m_components;

        // Befriend class for access
        friend class Punity::PEngine;

        static uint64_t entity_count;
        uint64_t m_id = entity_count++; // Increment id's

        // Parent entity and
        PEntity* m_parent_entity = nullptr;

        // Entity transform
        Components::PTransform* m_transform;

        bool m_is_active = true;
        bool m_is_destroyed = false;

        void report_enable_to_components();
        void report_disable_to_components();
        void report_update_to_components();
        void report_destroy_to_components();

        // Disable copy
        PEntity &operator=(const PEntity &);

        PEntity();
        explicit PEntity(std::string const& new_name);
    public:
        // Let's make sure we create entities dynamically.
        static PEntity* make_entity();
        static PEntity* make_entity(std::string const& new_name);

        void set_name(std::string const& new_name);
        void set_active(bool);
        void destroy();

        // Public read-only
        Components::PTransform* const& transform = m_transform;
        PEntity* const & parent_of_entity = m_parent_entity;
        std::string const& name = m_name;

        // Return all children entities
        std::list<PEntity*> const & get_children();

        bool has_child(PEntity* entity);

        void remove_child_entity(PEntity* entity);

        // Return components
        std::list<Punity::Components::PComponent*> const & get_all_components();


        // Add a new child entity
        void add_child(PEntity* entity);

        // Could use std::enable_if and std::is_base_of/std::is_convertible
        // so we dont compile for components not derived from PComponent.
        // But I'm done with this. I've wasted too much time.

        // Add a new component
        template <class T>
        void add_component() {
            // No checking if component exists, after all if
            // you mistakenly insert more than once component
            // you will still get the first component returned
            // to you.

            // Also, it costs time to find a component, so no, thanks.
            Components::PComponent* component = (Components::PComponent*)(new T);
            component->set_parent(this);
            m_components.push_front(component);
        }

        template <class T>
        T* get_component() {
            std::cout << m_components.size() << " yeah " << '\n';
            for (auto component : m_components) {
                // Cast to T*
                T* derived = dynamic_cast<T*>(component);
                if (derived != nullptr) {
                    return derived;
                }
            }
            return nullptr;
        }

        void set_parent(PEntity* parent);

        ~PEntity();
    };
}


#endif //_ENTITY_H
