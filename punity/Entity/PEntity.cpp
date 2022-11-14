//
// Created by god on 14.11.2022.
//

#include "PEntity.h"

uint64_t Punity::PEntity::entity_count = 0;

void Punity::PEntity::set_active(bool state) {
    m_is_active = state;

    // Activate children entities and children components
    for (auto child : m_children_entities) {
        child->set_active(state);
    }
    for (auto child : m_components) {
        child->set_active(state);
    }

    if (state) on_enable();
    else on_disable();
}

void Punity::PEntity::propagate_update() {
    // Propagate children entities and update children components
    std::cout << "propagate at " << m_name << '\n';
    for (auto child : m_children_entities) {
        child->propagate_update();
    }
    for (auto child : m_components) {
        child->on_update();
    }
}

std::list<Punity::PEntity*>& Punity::PEntity::get_children() {
    return m_children_entities;
}

void Punity::PEntity::add_child(Punity::PEntity *entity) {
    if (entity == this) Punity::Error("Cannot set entity child as self.");
    m_children_entities.push_back(entity);
    entity->set_parent(this);
}

std::list<Punity::Components::PComponent *> &Punity::PEntity::get_components() {
    return m_components;
}

void Punity::PEntity::add_component(Punity::Components::PComponent *component) {
    m_components.push_back(component);
    component->set_parent(this);
}

// TODO Update parent
void Punity::PEntity::set_parent(Punity::PEntity *parent) {
    m_parent_entity = parent;
}

void Punity::PEntity::set_name(const std::string &new_name) {
    m_name = new_name;
}
