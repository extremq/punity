//
// Created by god on 17.12.2022.
//

#ifndef _WEAPONPICKUP_H
#define _WEAPONPICKUP_H

#include "game/Logic/SceneManager.h"
#include "game/Assets/weapons.h"

namespace Game {
    class WeaponPickup : public Punity::Components::PComponent {
        // Start with an empty weapon
        Weapons::WeaponConfig stored_weapon = Weapons::empty_weapon;
    public:
        void set_weapon(Weapons::WeaponConfig chosen);
        Weapons::WeaponConfig swap_weapon(Weapons::WeaponConfig chosen);
    };
} // Game

#endif //_WEAPONPICKUP_H
