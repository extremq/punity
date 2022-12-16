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
    constexpr uint8_t COLLIDER_PLAYER_PROJECTILE_2 = 4;
    constexpr uint8_t COLLIDER_PLAYER_PROJECTILE_3 = 5;
    constexpr uint8_t COLLIDER_PLAYER_PROJECTILE_4 = 6;

    constexpr uint8_t COLLIDER_ENEMY_PROJECTILE_1 = 7;
    constexpr uint8_t COLLIDER_ENEMY_PROJECTILE_2 = 8;
    constexpr uint8_t COLLIDER_ENEMY_PROJECTILE_3 = 9;
    constexpr uint8_t COLLIDER_ENEMY_PROJECTILE_4 = 10;

    constexpr uint8_t COLLIDER_ENERGY_PICKUP = 11;
    constexpr uint8_t COLLIDER_HEART_PICKUP = 12;
}

#endif //_COLLIDERS_H
