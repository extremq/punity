//
// Created by god on 28.11.2022.
//

#include "PBoxCollider.h"
#include "punity/Utils/PCollisionComputation.h"
#include "punity/Utils/PError.h"

namespace Punity::Components {
    PBoxCollider::PBoxCollider() {
        m_shape = BOX;
    }

    bool PBoxCollider::solve_collision(PCollider *other) {
        Punity::Utils::Error("Box collisions not implemented.");
        return false;
    }

    PBoxCollider* PBoxCollider::set_size(float h, float w) {
        height = h;
        width = w;
        return this;
    }
} // Components