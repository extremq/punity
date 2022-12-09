//
// Created by god on 14.11.2022.
//

#include <iostream>
#include "PComponent.h"

uint64_t Punity::Components::PComponent::component_count = 0;

namespace Punity::Components {
    void PComponent::set_active(bool state) {
        // Don't do anything if this is the same state
        if (m_is_active == state) return;

        m_is_active = state;

        // Simple state management
        if (state) on_enable();
        else on_disable();
    }

    void PComponent::set_parent(Punity::PEntity *parent) {
        m_parent_entity = parent;
    }

    uint64_t PComponent::get_id() {
        return m_id;
    }

    bool PComponent::is_active() {
        return m_is_active;
    }

    Punity::PEntity* PComponent::get_entity() {
        return m_parent_entity;
    }

    // Empty functions
    void PComponent::on_enable() {

    }

    void PComponent::on_disable() {
        std::cout << "im disabled\n";
    }

    void PComponent::on_start_collision(PCollider *) {

    }

    void PComponent::on_end_collision(PCollider *) {

    }

    void PComponent::on_update() {

    }

    void PComponent::on_destroy() {

    }

    void PComponent::on_start() {

    }
} // Punity