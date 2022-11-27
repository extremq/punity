//
// Created by god on 26.11.2022.
//

#ifndef PUNITY_GAME_ENGINE_PCIRCLECOLLIDER_H
#define PUNITY_GAME_ENGINE_PCIRCLECOLLIDER_H

#include "PCollider.h"

namespace Punity {
    namespace Components {

        class PCircleCollider : PCollider {
        public:
            float radius = 0.0f;
            void solve_collisions(PCollider* other) override;
        };

    } // Punity
} // Components

#endif //PUNITY_GAME_ENGINE_PCIRCLECOLLIDER_H
