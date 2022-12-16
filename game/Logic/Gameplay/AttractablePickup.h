//
// Created by god on 16.12.2022.
//

#ifndef _PICKUP_H
#define _PICKUP_H

#include "game/Logic/SceneManager.h"

namespace Game {

    constexpr float INTERPOLATION_TIME = 1.5f;
    constexpr float APPROACHING_DISTANCE = 40.0f;

    // Class used by various pickups
    class AttractablePickup : public Punity::Components::PComponent {
        Punity::PEntity* player = nullptr;

        float time_of_approaching_start = 0;
        bool is_approaching_player = false;

        void on_update() override;
    };

} // Game

#endif //_PICKUP_H
