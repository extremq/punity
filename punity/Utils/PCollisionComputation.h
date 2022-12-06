//
// Created by god on 26.11.2022.
//

#ifndef _PCOLLISIONCOMPUTATION_H
#define _PCOLLISIONCOMPUTATION_H

#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"

namespace Punity::Collision {
    bool solve_circle_rect(Components::PCircleCollider* circle, Components::PBoxCollider* rect);
}

#endif //_PCOLLISIONCOMPUTATION_H
