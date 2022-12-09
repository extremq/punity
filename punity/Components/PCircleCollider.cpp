//
// Created by god on 26.11.2022.
//

#include "PCircleCollider.h"
#include "punity/Utils/PCollisionComputation.h"
#include "punity/Utils/PError.h"

namespace Punity::Components {
    bool PCircleCollider::solve_collision(PCollider* other) {
        switch (other->get_shape()) {
            case BOX:
                return Punity::Collision::solve_circle_rect(this, (PBoxCollider*) other);
            case CIRCLE:
                Punity::Utils::Error("Circle-Circle collision not defined.");
                return false;
        }
        return false;
    }

    PCircleCollider::PCircleCollider() {
        m_shape = CIRCLE;
    }

    PCircleCollider *PCircleCollider::set_radius(float r) {
        radius = r;
        // Used for chaining functions
        return this;
    }
} // Components