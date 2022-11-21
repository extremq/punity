//
// Created by god on 14.11.2022.
//

#include <iostream>
#include "PEntity.h"
#include "punity/Punity.h"
#include "punity/Components/PComponent.h"

uint64_t Punity::PEntity::entity_count = 0;

void Punity::PEntity::set_active(bool state) {
    // If the state is the same, nothing should happen.
    if (m_is_active == state) return;
        m_is_active = state;

    // If this is an enable, register ourselves
    // Otherwise, disables will be handled by the Engine
    if (state) {
        // Will report an enable event
        Punity::Engine.register_entity(this);
    }

    // Activate children entities
    for (auto child : m_children_entities) {
        child->set_active(state);
    }
}

std::list<Punity::PEntity*> const & Punity::PEntity::get_children() {
    return m_children_entities;
}

// Returns pointer to found child, if exists
bool Punity::PEntity::has_child(Punity::PEntity* entity) {
    for (auto child : m_children_entities) {
        if (child->m_id == entity->m_id) {
            return true;
        }
    }
    return false;
}

void Punity::PEntity::add_child(Punity::PEntity* entity) {
    if (entity == this) Punity::Utils::Error("Cannot set entity child as self.", m_name);

    // Search for child
    if (!has_child(entity)) {
        // Nothing found, insert it
        m_children_entities.push_back(entity);
        entity->m_parent_entity = this;
    }
    else
        Punity::Utils::Error("Inserting an entity child that already exists.", m_name);
}

std::list<Punity::Components::PComponent *> const &Punity::PEntity::get_all_components() {
    return m_components;
}

void Punity::PEntity::remove_child_entity(Punity::PEntity* entity) {
    // Let's swap the end with the removed entity.
    if (m_children_entities.empty()) Punity::Utils::Error("Trying to remove from childless entity.", m_name);

    Punity::PEntity* last = m_children_entities.back();
    for (auto it = m_children_entities.begin(); it != m_children_entities.end(); ++it) {
        if ((*it)->m_id == entity->m_id) {

            // Maybe it's the end, then no need to save
            if ((it != m_children_entities.end()) && (it == --m_children_entities.end())) {
                m_children_entities.pop_back();
                return;
            }

            m_children_entities.pop_back();
            (*it) = last;
            return;
        }
    }
}

void Punity::PEntity::set_parent(Punity::PEntity* parent) {
    std::cout << "setting parent of " << name << " to " << parent->name << '\n';

    if (parent->m_is_destroyed) Punity::Utils::Error("Setting as parent a destroyed entity.", m_name);

    if (m_parent_entity != nullptr && !m_parent_entity->m_children_entities.empty()) {
        m_parent_entity->remove_child_entity(this);
    }

    // And update the parent entity
    parent->add_child(this);

    // Update parent pointer
    m_parent_entity = parent;
}

void Punity::PEntity::set_name(const std::string &new_name) {
    m_name = new_name;
}

Punity::PEntity::PEntity(const std::string &new_name) {
    // Set transform up
    m_transform = add_component<Components::PTransform>();

    // Any Entity should have the root_entity as a default parent
    // Except for root itself
    if (new_name != "__Root") {
        m_name = new_name;
        set_parent(Punity::Engine.root_entity);
        Punity::Engine.register_entity(this);
    }
    else {
        // Also set name for root, but dont set any parent nor register
        m_name = new_name;
    }
}

Punity::PEntity::PEntity() {
    // Set transform up
    m_transform = add_component<Components::PTransform>();

    // Any Entity should have the root_entity as a default parent
    set_parent(Punity::Engine.root_entity);
    Punity::Engine.register_entity(this);
}

void Punity::PEntity::destroy() {
    m_is_destroyed = true;
    m_is_active = false;

    // Also mark the subtree inactive.
    // A destroyed component is also inactive.
    // Destruction has priority over disabling in event execution order.

    std::cout << "destroyed " << m_name << '\n';

    // Mark children entities as destroyed, next frame takes effect
    for (auto child : m_children_entities) {
        child->destroy();
    }
}

void Punity::PEntity::report_enable_to_components() {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_enable();
        }
    }
}

// Called by the engine on disabling
void Punity::PEntity::report_disable_to_components() {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_disable();
        }
    }
}

void Punity::PEntity::report_update_to_components() {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_update();
        }
    }
}

// Called by the engine on disabling
void Punity::PEntity::report_destroy_to_components() {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_destroy();
        }
    }
}

void Punity::PEntity::report_start_to_components() {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_start();
        }
    }
}

Punity::PEntity::~PEntity() {
    delete m_transform;
    for (auto component : m_components) {
        delete component;
    }
    std::cout << "Destructor called for " << name << '\n';
}

Punity::PEntity *Punity::PEntity::make_entity() {
    // Create and return a reference to entity
    return new PEntity();
}

Punity::PEntity *Punity::PEntity::make_entity(const std::string &new_name) {
    // Create and return a reference to entity
    return new PEntity(new_name);
}
