//
// Created by god on 14.12.2022.
//

#ifndef _WEAPONS_H
#define _WEAPONS_H

#include <cstdint>

namespace Game::Weapons {
    struct WeaponConfig {
        uint8_t bullet_count = 1;
        float shots_per_second = 1.0f;
        float attack_radius_degrees = 0;
        float bullet_speed = 30.0f;
    };

    extern const WeaponConfig empty_weapon;
    extern const WeaponConfig starting_weapon;
    extern const WeaponConfig enemy_weapon;
    extern const WeaponConfig rifle;
}


#endif //_WEAPONS_H
