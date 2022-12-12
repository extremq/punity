//
// Created by god on 12.12.2022.
//

#ifndef _WEAPON_H
#define _WEAPON_H

#include "game/Logic/SceneManager.h"

namespace Game {

    // Configurable weapon
    class Weapon : public Punity::Components::PComponent {
    private:
        uint8_t bullet_count = 1;
        float shots_per_second = 1.0f;
        float attack_radius_degrees = 0;
        float bullet_speed = 30.0f;
        float last_shoot_time = 0.0f;
    public:
        Weapon* set_shots_per_second(float bullets);
        Weapon* set_bullet_count(uint8_t count);
        Weapon* set_attack_radius_degrees(float radius);
        Weapon* set_bullet_speed(float speed);

        void shoot(Punity::Utils::PVector start_pos, Punity::Utils::PVector target_pos, Punity::PEntity* parent, bool is_player);

        Punity::Utils::PVector rotate_vector(Punity::Utils::PVector vector, float degrees);
    };

} // Game

#endif //_WEAPON_H
