//
// Created by god on 14.12.2022.
//

#include "weapons.h"

namespace Game::Weapons {
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
        10,
        Colliders::PLAYER_PROJECTILE_1,
        0,
        1,
        1.0f,
        15.0f,
        100.0f
    };

    const WeaponConfig enemy_weapon_1_shotgun = {
            3,
            Colliders::ENEMY_PROJECTILE_1,
            3,
            1,
            0.5f,
            75.0f,
            40.0f
    };

    const WeaponConfig enemy_weapon_2_shotgun = {
            5,
            Colliders::ENEMY_PROJECTILE_1,
            3,
            1,
            0.5f,
            60.0f,
            40.0f
    };

    const WeaponConfig enemy_weapon_3_shotgun = {
            3,
            Colliders::ENEMY_PROJECTILE_2,
            3,
            2,
            0.5f,
            75.0f,
            40.0f
    };

    const WeaponConfig enemy_weapon_1_rifle = {
            1,
            Colliders::ENEMY_PROJECTILE_1,
            1,
            1,
            3.0f,
            0.0f,
            40.0f
    };

    const WeaponConfig enemy_weapon_2_rifle = {
            1,
            Colliders::ENEMY_PROJECTILE_1,
            1,
            1,
            5.0f,
            0.0f,
            40.0f
    };

    const WeaponConfig enemy_weapon_3_rifle = {
            1,
            Colliders::ENEMY_PROJECTILE_2,
            1,
            2,
            5.0f,
            0.0f,
            40.0f
    };

    const WeaponConfig common_rifle  = {
            1,
            Colliders::PLAYER_PROJECTILE_1,
            2,
            1,
            5.0f,
            0.0f,
            100.0f
    };

    const WeaponConfig rare_rifle = {
            1,
            Colliders::PLAYER_PROJECTILE_2,
            3,
            2,
            7.5f,
            0.0f,
            100.0f
    };

    const WeaponConfig common_shotgun = {
            5,
            Colliders::PLAYER_PROJECTILE_1,
            3,
            1,
            1.5f,
            75.0f,
            100.0f
    };

    const WeaponConfig rare_shotgun = {
            5,
            Colliders::PLAYER_PROJECTILE_2,
            5,
            2,
            1.5f,
            60.0f,
            100.0f
    };

    const WeaponConfig common_sniper = {
            1,
            Colliders::PLAYER_PROJECTILE_3,
            3,
            3,
            1.0f,
            0.0f,
            200.0f
    };

    const WeaponConfig rare_sniper = {
            2,
            Colliders::PLAYER_PROJECTILE_3,
            5,
            3,
            1.0f,
            5.0f,
            200.0f
    };

    extern const WeaponConfig enemy_weapons[6] = {
            enemy_weapon_1_rifle,
            enemy_weapon_1_shotgun,
            enemy_weapon_2_rifle,
            enemy_weapon_2_shotgun,
            enemy_weapon_3_rifle,
            enemy_weapon_3_shotgun
    };

    const WeaponConfig rare_weapons[3] = {
            rare_rifle,
            rare_shotgun,
            rare_sniper
    };

    const WeaponConfig common_weapons[3] = {
            common_rifle,
            common_shotgun,
            common_sniper
    };
}
