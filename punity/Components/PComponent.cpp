//
// Created by god on 14.11.2022.
//

#include "PComponent.h"

uint64_t Punity::Components::PComponent::component_count = 0;

namespace Punity::Components {
    void PComponent::set_active(bool state) {
        m_is_active = state;

        // Simple state management
        if (state) on_enable();
        else on_disable();
    }

    void PComponent::set_parent(Punity::PEntity *parent) {
        m_parent_entity = parent;
    }
} // Punity