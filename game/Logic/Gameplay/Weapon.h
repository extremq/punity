//
// Created by god on 12.12.2022.
//

#ifndef _WEAPON_H
#define _WEAPON_H

#include "game/Logic/SceneManager.h"
#include "game/Assets/weapons.h"

namespace Game {

    // Configurable weapon
    class Weapon : public Punity::Components::PComponent {
    private:
        Weapons::WeaponConfig config = Weapons::starting_weapon;
        float last_shoot_time = 0.0f;
    public:
        Weapon* set_shots_per_second(float bullets);
        Weapon* set_bullet_count(uint8_t count);
        Weapon* set_projectile_type(uint8_t type);
        Weapon* set_attack_radius_degrees(float radius);
        Weapon* set_bullet_speed(float speed);

        void set_weapon(Weapons::WeaponConfig weaponConfig);

        uint8_t get_bullet_count();
        uint8_t get_energy_cost();
        uint8_t get_projectile_type();

        void shoot(Punity::Utils::PVector start_pos, Punity::Utils::PVector target_pos, Punity::PEntity* parent, bool is_player);

        Punity::Utils::PVector rotate_vector(Punity::Utils::PVector vector, float degrees);
    };

} // Game

#endif //_WEAPON_H
