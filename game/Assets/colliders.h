//
// Created by god on 14.12.2022.
//

#ifndef _COLLIDERS_H
#define _COLLIDERS_H

#include <cstdint>

namespace Game::Colliders {
    // Codes used by collider info
    constexpr uint8_t COLLIDER_PLAYER = 1;
    constexpr uint8_t COLLIDER_ENEMY = 2;
    constexpr uint8_t COLLIDER_PLAYER_PROJECTILE_1 = 3;
    constexpr uint8_t COLLIDER_ENEMY_PROJECTILE_1 = 4;

}

#endif //_COLLIDERS_H
