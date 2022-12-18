//
// Created by god on 14.12.2022.
//

#include "weapons.h"

namespace Game::Weapons {

    uint8_t bullet_count = 1;
    uint8_t projectile_type = 0;
    uint8_t energy_cost = 0;
    float shots_per_second = 1.0f;
    float attack_radius_degrees = 0;
    float bullet_speed = 30.0f;

    const WeaponConfig empty_weapon {
        0,
        0,
        0,
        0,
        1.0f,
        0,
        100.0f
    };

    const WeaponConfig starting_weapon = {
        1,
        Colliders::PLAYER_PROJECTILE_3,
        0,
        3,
        1.0f,
        0.0f,
        100.0f
    };

    const WeaponConfig enemy_weapon = {
            2,
            Colliders::ENEMY_PROJECTILE_1,
            0,
            1,
            0.33f,
            15.0f,
            30.0f
    };

    const WeaponConfig rifle = {
            1,
            Colliders::PLAYER_PROJECTILE_1,
            2,
            1,
            5.0f,
            0.0f,
            100.0f
    };
}
