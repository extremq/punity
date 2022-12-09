//
// Created by god on 26.11.2022.
//

#ifndef _PCIRCLECOLLIDER_H
#define _PCIRCLECOLLIDER_H

#include "PCollider.h"

namespace Punity::Components {
    class PCircleCollider : public PCollider {
    public:
        PCircleCollider();
        float radius = 0.0f;
        PCircleCollider* set_radius(float r);
        bool solve_collision(PCollider* other) override;
    };

} // Components

#endif //_PCIRCLECOLLIDER_H
