//
// Created by god on 12.12.2022.
//

#include "Weapon.h"
#include "GameplayPrefabCreator.h"
#include "Projectile.h"

namespace Game {
    Weapon *Weapon::set_shots_per_second(float bullets) {
        config.shots_per_second = bullets;
        return this;
    }

    Weapon *Weapon::set_bullet_count(uint8_t count) {
        config.bullet_count = count;
        return this;
    }

    Weapon *Weapon::set_attack_radius_degrees(float radius) {
        config.attack_radius_degrees = radius;
        return this;
    }

    Weapon *Weapon::set_bullet_speed(float speed) {
        config.bullet_speed = speed;
        return this;
    }

    void Weapon::shoot(Punity::Utils::PVector start_pos, Punity::Utils::PVector target_pos, Punity::PEntity* parent, bool is_player) {
        if (Punity::Time.time - last_shoot_time >= 1.0f / config.shots_per_second) {
            last_shoot_time = Punity::Time.time;

            // Computation of bullet spread
            Punity::Utils::PVector rotated_target_around = target_pos - start_pos, computed_rotation;
            rotated_target_around = rotate_vector(rotated_target_around, - config.attack_radius_degrees / 2.0f);
            for (int i = 0; i < config.bullet_count; ++i) {
                Punity::PEntity* bullet;
                if (is_player)
                    bullet = GameplayPrefabCreator::make_player_bullet(parent);
                else
                    bullet = GameplayPrefabCreator::make_enemy_bullet(parent);

                // Set the spawn position
                bullet->get_transform()->set_global(start_pos);

                if (config.bullet_count == 1) {
                    // If there's one bullet just send it straight to the target
                    bullet->get_component<Projectile>()
                            ->set_target_point(target_pos)
                            ->set_speed(config.bullet_speed)
                            ->set_self(config.projectile_type);
                    continue;
                }

                // Add rotation
                computed_rotation = rotate_vector(rotated_target_around, i * config.attack_radius_degrees / (config.bullet_count - 1));

                // Translate back
                computed_rotation += start_pos;

                bullet->get_component<Projectile>()
                        ->set_target_point(computed_rotation)
                        ->set_speed(config.bullet_speed)
                        ->set_self(config.projectile_type);
            }
        }
    }

    Punity::Utils::PVector Weapon::rotate_vector(Punity::Utils::PVector vector, float degrees) {
        float x = vector.x, y = vector.y;
        // Convert to radians
        float radians = degrees * 0.01745327777f;
        vector.x = x * std::cos(radians) - y * std::sin(radians);
        vector.y = x * std::sin(radians) + y * std::cos(radians);

        return vector;
    }

    void Weapon::set_weapon(Weapons::WeaponConfig weaponConfig) {
        config = weaponConfig;
    }

    uint8_t Weapon::get_bullet_count() {
        return config.bullet_count;
    }

    uint8_t Weapon::get_energy_cost() {
        return config.energy_cost;
    }

    uint8_t Weapon::get_projectile_type() {
        return config.projectile_type;
    }
} // Game