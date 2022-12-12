//
// Created by god on 26.11.2022.
//

#ifndef _PCOLLISIONCOMPUTATION_H
#define _PCOLLISIONCOMPUTATION_H

#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"
#include "punity/Utils/PVector.h"

namespace Punity::Collision {
    bool solve_circle_rect(Components::PCircleCollider* circle, Components::PBoxCollider* rect);
    bool solve_circle_circle(Components::PCircleCollider* circle1, Components::PCircleCollider* circle2);

    float distance(Punity::Utils::PVector const& a, Punity::Utils::PVector const& b);
}

#endif //_PCOLLISIONCOMPUTATION_H
