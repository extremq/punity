//
// Created by god on 28.11.2022.
//

#ifndef _PBOXCOLLIDER_H
#define _PBOXCOLLIDER_H

#include "PCollider.h"

namespace Punity::Components {
    class PBoxCollider : public PCollider {
    public:
        float width = 0.0f, height = 0.0f;
        PBoxCollider();
        bool solve_collision(PCollider* other) override;
    };

} // Components

#endif //_PBOXCOLLIDER_H
