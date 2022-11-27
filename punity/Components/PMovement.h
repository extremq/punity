//
// Created by god on 18.11.2022.
//

#ifndef _PMOVEMENT_H
#define _PMOVEMENT_H

#include "punity/Punity.h"
#include "PSpriteRenderer.h"

namespace Punity::Components {
    class PMovement : public PComponent {
        bool active = false;
        float last = 0;
        void on_update() override {
            Utils::PVector direction;
            direction.x = Punity::Joystick.get_x_direction();
            direction.y = Punity::Joystick.get_y_direction();
            direction = direction * 30.0f * Punity::Time.delta_time;
            entity->transform->translate(direction);
            Punity::Screen.camera = entity->transform->global_position;
        }
    };

} // Components

#endif //_PMOVEMENT_H
