//
// Created by god on 12.12.2022.
//

#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "game/Logic/SceneManager.h"

namespace Game {
    // Attaching this to an entity makes it behave like a projectile
    class Projectile : public Punity::Components::PComponent {
    private:
        // Normalized direction!
        Punity::Utils::PVector direction = {1, 0};
        float speed = 30.0f;
        uint8_t exception = 0;
        uint8_t self = 0;

        void on_update() override;

        void on_start_collision(Punity::Components::PCollider* other) override;
    public:
        Projectile* set_target_point(Punity::Utils::PVector target_point);
        Projectile* set_exception(uint8_t exp);
        Projectile* set_self(uint8_t _self);
    };
}

#endif //_PROJECTILE_H
