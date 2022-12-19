//
// Created by god on 14.12.2022.
//

#ifndef _WEAPONS_H
#define _WEAPONS_H

#include <cstdint>
#include "colliders.h"

namespace Game::Weapons {
    struct WeaponConfig {
        uint8_t bullet_count = 1;
        uint8_t projectile_type = 0;
        uint8_t energy_cost = 0;
        uint8_t damage = 0;
        float shots_per_second = 1.0f;
        float attack_radius_degrees = 0;
        float bullet_speed = 30.0f;
    };

    extern const WeaponConfig empty_weapon;
    extern const WeaponConfig starting_weapon;
    extern const WeaponConfig enemy_weapon_1_shotgun;
    extern const WeaponConfig enemy_weapon_1_rifle;
    extern const WeaponConfig enemy_weapon_2_shotgun;
    extern const WeaponConfig enemy_weapon_2_rifle;
    extern const WeaponConfig enemy_weapon_3_shotgun;
    extern const WeaponConfig enemy_weapon_3_rifle;
    extern const WeaponConfig common_rifle;
    extern const WeaponConfig rare_rifle;
    extern const WeaponConfig common_shotgun;
    extern const WeaponConfig rare_shotgun;
    extern const WeaponConfig common_sniper;
    extern const WeaponConfig rare_sniper;
    extern const WeaponConfig enemy_weapons[6];
    extern const WeaponConfig rare_weapons[3];
    extern const WeaponConfig common_weapons[3];
}


#endif //_WEAPONS_H
