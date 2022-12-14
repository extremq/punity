//
// Created by god on 14.12.2022.
//

#include "weapons.h"

namespace Game::Weapons {

    const WeaponConfig empty_weapon {
        0,
        1.0f,
        0,
        100.0f
    };

    const WeaponConfig starting_weapon = {
        1,
        10.0f,
        0,
        100.0f,
    };

    const WeaponConfig enemy_weapon = {
            2,
            0.33f,
            15.0f,
            50.0f,
    };

    const WeaponConfig rifle = {
            1,
            5.0f,
            0,
            100.0f
    };
}
