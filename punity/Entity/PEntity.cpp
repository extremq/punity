//
// Created by god on 14.11.2022.
//

#include <iostream>
#include "PEntity.h"
#include "punity/Punity.h"
#include "punity/Components/PComponent.h"
#include "punity/Utils/PError.h"

uint64_t Punity::PEntity::entity_count = 0;

void Punity::PEntity::activate_global_state_of_children() {
    for (auto child: m_children_entities) {
        if (child->is_self_active()) {
            // The child is also self active! Propagate!
            child->m_globally_active = true;
            Punity::Engine.register_entity(child);
            child->activate_global_state_of_children();
        }
    }
}

void Punity::PEntity::deactivate_global_state_of_children() {
    for (auto child: m_children_entities) {
        if (child->is_self_active()) {
            // The child is also self active! Propagate!
            child->m_globally_active = false;
            child->deactivate_global_state_of_children();
        }
    }
}

void Punity::PEntity::set_active(bool state) {
    // Don't call the root entity, bro
    if (m_id == 0) Punity::Utils::Error("Don't use set_active on __Root.");

    // Same state, no need to change anything
    if (state == m_self_active) return;

    // Check if the parent is globally active.
    // Otherwise, the change has no effect.
    if (m_parent_entity->is_globally_active()) {

        // Oh, so we are globally active?
        // Notify the rest of the squad
        if (state) {
            m_globally_active = true;
            activate_global_state_of_children();
            Punity::Engine.register_entity(this);
        } else {
            m_globally_active = false;
            deactivate_global_state_of_children();
        }
    }
    else {
        m_globally_active = false;
    }

    // Commit activeness
    m_self_active = state;
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
    if (parent == nullptr) Punity::Utils::Error("Don't use set_parent on null entity.");

    if (m_id == 0) Punity::Utils::Error("Don't use set_parent on __Root.");

    if (parent->m_is_destroyed) Punity::Utils::Error("Setting as parent a destroyed entity.", m_name);
    std::cout << "setting parent of " << m_name << " to " << parent->m_name << '\n';

    if (m_parent_entity != nullptr && !m_parent_entity->m_children_entities.empty()) {
        m_parent_entity->remove_child_entity(this);
    }

    // And update the parent entity
    parent->add_child(this);

    // Update parent pointer
    m_parent_entity = parent;

    // Also force a state update on entity and its children
    if (m_self_active) {
        // We're self_active, so that should mean we need to check the parent's status
        if (m_parent_entity->is_globally_active()) {
            m_globally_active = true;

            // Also register! We already register the children
            Punity::Engine.register_entity(this);

            activate_global_state_of_children();
        }
        else {
            m_globally_active = false;
            deactivate_global_state_of_children();
        }
    }
}

void Punity::PEntity::set_name(const std::string &new_name) {
    if (m_id == 0) Punity::Utils::Error("Don't use set_name on __Root.");
    m_name = new_name;
}

Punity::PEntity::PEntity(const std::string &new_name, bool is_active) {
    // Set transform up
    m_transform = add_component<Components::PTransform>();

    // Any Entity should have the root_entity as a default parent
    // Except for root itself
    if (m_id != 0) {
        m_name = new_name;
        m_self_active = is_active;
        set_parent(Punity::Engine.root_entity);
    }
    else {
        // Also set name for root, but dont set any parent nor register
        m_globally_active = true;
        m_self_active = true;
        m_name = new_name;
    }
}

Punity::PEntity::PEntity(const std::string &new_name, Punity::PEntity *parent_entity, bool is_active) {
    // Set transform up
    m_transform = add_component<Components::PTransform>();

    if (m_id == 0) Punity::Utils::Error("Cannot set parent of Root entity.");

    m_name = new_name;
    m_self_active = is_active;

    // Set the parent - this also triggers an update of states
    set_parent(parent_entity);
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
    m_globally_active = false;
    m_self_active = false;

    // Also mark the subtree inactive.
    // A destroyed component is also inactive.
    // Destruction has priority over disabling in event execution order.

    std::cout << "destroyed " << m_name << '\n';

    Engine.queue_destruction(this);

    // Mark children entities as destroyed, next frame takes effect
    for (auto child : m_children_entities) {
        child->destroy();
    }
}

void Punity::PEntity::destroy_children() {
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


void Punity::PEntity::report_start_collision_to_components(Components::PCollider* col) {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_start_collision(col);
        }
    }
}

void Punity::PEntity::report_end_collision_to_components(Components::PCollider* col) {
    for (auto component : m_components) {
        if (component->m_is_active) {
            component->on_end_collision(col);
        }
    }
}

Punity::PEntity::~PEntity() {
    for (auto component : m_components) {
        delete component;
//        std::cout << "component called for " << name << '\n';
    }
    std::cout << "Destructor called for " << m_name << '\n';
}

Punity::PEntity *Punity::PEntity::make_entity(const std::string &new_name, bool is_active) {
    // Create and return a reference to entity
    return new PEntity(new_name, is_active);
}

Punity::PEntity *Punity::PEntity::make_entity(const std::string &new_name, Punity::PEntity *parent_entity, bool is_active) {
    return new PEntity(new_name, parent_entity, is_active);
}

bool Punity::PEntity::is_globally_active() {
    return m_globally_active;
}

bool Punity::PEntity::is_self_active() {
    return m_self_active;
}

uint64_t Punity::PEntity::get_id() {
    return m_id;
}

std::string Punity::PEntity::get_name() {
    return m_name;
}

Punity::PEntity *Punity::PEntity::get_parent() {
    return m_parent_entity;
}

Punity::Components::PTransform *Punity::PEntity::get_transform() {
    return m_transform;
}

void Punity::PEntity::print_tree(uint8_t level) {
    for (uint8_t i = 0; i < level; ++i) {
        std::cout << '\t';
    }

    if (m_globally_active) {
        std::cout << "+";
    }
    else {
        std::cout << "-";
    }

    std::cout << " '" << m_name << "', self: ";
    if (m_self_active) {
        std::cout << "true";
    }
    else {
        std::cout << "false";
    }

    std::cout << '\n';

    for (auto child : m_children_entities) {
        child->print_tree(level + 1);
    }
}

size_t Punity::PEntity::get_children_count() {
    return m_children_entities.size();
}

Punity::PEntity *Punity::PEntity::get_child_by_name(std::string name) {
    // returns FIRST child with same name
    for (auto child : m_children_entities) {
        if (name == child->m_name) {
            return child;
        }
    }

    return nullptr;
}
