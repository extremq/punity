//
// Created by god on 26.11.2022.
//

#include "PCollider.h"
#include "punity/Entity/PEntity.h"

namespace Punity::Components {
    PCollider* PCollider::check_if_exists_as_collider(PCollider *other) {
        if (m_colliders.find(other->get_id()) != m_colliders.end())
            return m_colliders[other->get_id()];
        return nullptr;
    }

    void PCollider::delete_collider(PCollider *other) {
        m_colliders.erase(other->get_id());
    }

    void PCollider::add_collider(PCollider *other) {
        m_colliders.insert({other->get_id(), other});
    }

    // Update and notify the respective collider
    void PCollider::on_destroy() {
        for (auto collider : m_colliders) {
            collider.second->delete_collider(this);

            collider.second->get_entity()->report_end_collision_to_components(this);
        }

        m_colliders.clear();
    }

    void PCollider::on_disable() {
        for (auto collider : m_colliders) {
            collider.second->delete_collider(this);
            // Only notify their component, ours is inactive anyways
            collider.second->get_entity()->report_end_collision_to_components(this);
        }

        m_colliders.clear();
    }

    PCollider *PCollider::set_static(bool _static) {
        is_static = _static;

        return this;
    }

    PCollider *PCollider::set_trigger(bool _trigger) {
        is_trigger = _trigger;

        return this;
    }

    PCollider *PCollider::set_information(uint8_t _information) {
        information = _information;

        return this;
    }
} // Components