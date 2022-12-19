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
        bool touched_chest = false;
        bool using_starting_weapon = true;
        bool picked_up_any_weapon = false;

        // Avoid some casts
        Punity::PEntity* enemies = nullptr;
        Punity::PEntity* room = nullptr;
        Weapon* weapon_component = nullptr;

        // Weapon picked up by player
        Weapons::WeaponConfig equipped_weapon = Weapons::empty_weapon;

        // Weapons use energy
        int16_t remaining_energy = 99;

        float last_joystick_click_time = 0.0f;
        Punity::Components::PCollider* weapon_collided_with = nullptr;

        void on_start_collision(Punity::Components::PCollider* other) override;
        void on_collision(Punity::Components::PCollider* other) override;
        void on_update() override;
        void on_enable() override;

        void change_weapon(Weapons::WeaponConfig weaponConfig);
        void compute_damage_dealt_by_projectile(uint8_t projectile_type);

        void compute_movement();
        void reset_status_for_new_stage();

        Punity::Utils::PVector compute_nearest_enemy();
    public:
        bool is_using_starting_weapon();
        int16_t get_remaining_energy();
        void fully_reset_player();
        bool has_touched_chest();
        bool has_picked_up_any_weapon();
        Weapons::WeaponConfig get_equipped_weapon();
    };
} // Game

#endif //_PLAYERBEHAVIOUR_H
