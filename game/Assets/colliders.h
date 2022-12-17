//
// Created by god on 14.12.2022.
//

#ifndef _COLLIDERS_H
#define _COLLIDERS_H

#include <cstdint>

namespace Game::Colliders {
    // Codes used by collider info
    constexpr uint8_t PLAYER = 1;
    constexpr uint8_t ENEMY = 2;

    constexpr uint8_t PLAYER_PROJECTILE_1 = 3;
    constexpr uint8_t PLAYER_PROJECTILE_2 = 4;
    constexpr uint8_t PLAYER_PROJECTILE_3 = 5;
    constexpr uint8_t PLAYER_PROJECTILE_4 = 6;

    constexpr uint8_t ENEMY_PROJECTILE_1 = 7;
    constexpr uint8_t ENEMY_PROJECTILE_2 = 8;
    constexpr uint8_t ENEMY_PROJECTILE_3 = 9;
    constexpr uint8_t ENEMY_PROJECTILE_4 = 10;

    constexpr uint8_t ENERGY_PICKUP = 11;
    constexpr uint8_t HEART_PICKUP = 12;
    constexpr uint8_t WEAPON_PICKUP = 13;
}

#endif //_COLLIDERS_H
