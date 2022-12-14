//
// Created by god on 08.12.2022.
//

#ifndef _PLAYERBEHAVIOUR_H
#define _PLAYERBEHAVIOUR_H

#include "punity/Punity.h"
#include "Weapon.h"

namespace Game {
    class PlayerBehaviour : public Punity::Components::PComponent {
    private:
        bool m_has_touched_chest = false;
        bool m_is_using_starting_weapon = true;
        bool m_has_picked_up_any_weapon = false;

        // Avoid some casts
        Punity::PEntity* enemies = nullptr;
        Punity::PEntity* room = nullptr;
        Weapon* weapon_component = nullptr;

        // Weapon picked up by player
        Weapons::WeaponConfig equipped_weapon = Weapons::empty_weapon;

        // Weapons use bullets
        int16_t remaining_bullets = 100;

        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;

        void change_weapon(Weapons::WeaponConfig weaponConfig);

        void compute_movement();
        void reset_status_for_new_stage();

        Punity::Utils::PVector compute_nearest_enemy();
    public:
        void fully_reset_player();
        bool has_touched_chest();
    };
} // Game

#endif //_PLAYERBEHAVIOUR_H
