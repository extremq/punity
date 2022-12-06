//
// Created by god on 05.12.2022.
//

#ifndef _FLOATINGUI_H
#define _FLOATINGUI_H

#include "punity/Punity.h"

namespace Game {
    class FloatingUI : public Punity::Components::PComponent {
    private:
        void on_update() override {
           auto sprite = get_entity()->get_component<Punity::Components::PUISpriteRenderer>();
           sprite->ui_position.y = (float) sin(Punity::Time.time * speed) * scale + base_y;
        }
    public:
        float base_y = 0.0f;
        float scale = 1.0f;
        float speed = 1.0f;
    };

} // Game

#endif //_FLOATINGUI_H
