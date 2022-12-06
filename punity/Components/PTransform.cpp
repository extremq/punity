//
// Created by god on 14.11.2022.
//

#include "PTransform.h"
#include "punity/Engine/PEngine.h"
#include "punity/Entity/PEntity.h"

// After all setting a local value is the same as setting a global value.
// It will always be relative to the parent
void Punity::Components::PTransform::set_local(Punity::Utils::PVector const& local) {
    set_global(get_entity()->get_parent()->get_transform()->m_global_position + local);
}

void Punity::Components::PTransform::set_global(Punity::Utils::PVector const& global) {
    // Compute offset amount
    m_local_position = global - get_entity()->get_parent()->get_transform()->m_global_position;
    // Propagate to children
    update_position_of_children();
}

// Computes new coordinates based on parent
void Punity::Components::PTransform::update_position_of_children() {
    m_global_position = m_local_position + get_entity()->get_parent()->get_transform()->m_global_position;

    // Propagate to children
    auto children = get_entity()->get_children();
    for (auto child : children) {
        child->get_transform()->update_position_of_children();
    }
}

void Punity::Components::PTransform::translate(Punity::Utils::PVector const& tr) {
    set_global(m_global_position + tr);
}
