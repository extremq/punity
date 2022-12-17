//
// Created by god on 14.11.2022.
//
#ifndef _ENTITY_H
#define _ENTITY_H
#include <typeinfo>

#include "punity/Components/PComponent.fwd.h"
#include "punity/Engine/PEngine.fwd.h"
#include "punity/Components/PTransform.h"
#include "punity/Utils/PError.h"

#include <cstdint>
#include <string>
#include <list>
#include <iostream>

namespace Punity {
    namespace Components {
        class PCollider; // Small forward iteration for pointer
    }

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
        friend class Components::PCollider;

        static uint64_t entity_count;
        uint64_t m_id = entity_count++; // Increment id's

        // Parent entity and
        PEntity* m_parent_entity = nullptr;

        // Entity transform
        Components::PTransform* m_transform;

        bool m_self_active = false;
        bool m_globally_active = false;
        bool m_is_destroyed = false;

        void activate_global_state_of_children();
        void deactivate_global_state_of_children();

        void report_enable_to_components();
        void report_disable_to_components();
        void report_update_to_components();
        void report_destroy_to_components();
        void report_start_to_components();
        void report_start_collision_to_components(Components::PCollider*);
        void report_collision_to_components(Components::PCollider*);
        void report_end_collision_to_components(Components::PCollider*);

        // Disable copy
        PEntity &operator=(const PEntity &);

        PEntity();
        explicit PEntity(std::string const& new_name, bool is_active);
        PEntity(std::string const& new_name, PEntity* parent_entity, bool is_active);
    public:
        // Let's make sure we create entities dynamically.
        static PEntity* make_entity(std::string const& new_name, bool is_active);
        static PEntity* make_entity(std::string const& new_name, PEntity* parent_entity, bool is_active);

        // Methods
        void set_name(std::string const& new_name);
        void set_parent(PEntity* parent);
        void set_active(bool);
        void destroy();
        void destroy_children();
        void remove_child_entity(PEntity* entity);
        void print_tree(uint8_t level);
        void add_child(PEntity* entity);
        size_t get_children_count();
        bool has_child(PEntity* entity);
        bool is_globally_active();
        bool is_self_active();
        std::list<PEntity*> const & get_children();
        std::list<Punity::Components::PComponent*> const & get_all_components();
        uint64_t get_id();
        std::string get_name();
        PEntity* get_parent();
        PEntity* get_child_by_name(std::string name);
        Components::PTransform* get_transform();

        // Could use std::enable_if and std::is_base_of/std::is_convertible
        // so we dont compile for components not derived from PComponent.
        // But I'm done with this. I've wasted too much time.

        // Add a new component
        template <class T>
        T* add_component() {
            // Check if the component exists already
            if (get_component<T>() != nullptr) Punity::Utils::Error("Cannot add same component twice.", m_name);

            // Also, it costs time to find a component, so no, thanks.
            Components::PComponent* component = (Components::PComponent*)(new T);
            component->set_parent(this);

            // I push it to the front because it may save a few dynamic casts.
            // That's because it's more likely you will use an added component.
            m_components.push_front(component);

            // If this entity is active, call on_enable on the component
            if (m_globally_active && m_self_active) {
                component->on_enable();
            }

            return (T*) component;
        }

        template <class T>
        T* get_component() {
            for (auto component : m_components) {
                // Cast to T*
                T* derived = dynamic_cast<T*>(component);
                if (derived != nullptr) {
                    return derived;
                }
            }
            return nullptr;
        }

        ~PEntity();
    };
}


#endif //_ENTITY_H
