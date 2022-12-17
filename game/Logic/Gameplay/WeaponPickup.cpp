//
// Created by god on 17.12.2022.
//

#include "WeaponPickup.h"

namespace Game {
    void WeaponPickup::set_weapon(Weapons::WeaponConfig chosen) {
        stored_weapon = chosen;
    }

    Weapons::WeaponConfig WeaponPickup::swap_weapon(Weapons::WeaponConfig chosen) {
        // Swap the two weapons
        std::swap(stored_weapon, chosen);

        return chosen;
    }
} // Game