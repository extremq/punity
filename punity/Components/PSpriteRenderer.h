//
// Created by god on 12.11.2022.
//

#ifndef _PSPRITE_RENDERER_H
#define _PSPRITE_RENDERER_H

#include <iostream>
#include "PComponent.h"
#include "punity/Punity.h"

namespace Punity::Components {
    class PSpriteRenderer : public PComponent {
    private:
        // Pointer to const
        // Shared memory, of course!
        // All modifiers are applied at draw-stage
        uint16_t const * m_sprite = nullptr;
        uint16_t m_height = 0;
        uint16_t m_width = 0;
    public:
        void set_sprite(uint16_t const * sprite, uint16_t h, uint16_t w) {
            m_sprite = sprite;
            m_height = h;
            m_width = w;
        }

        void on_update() override {
            Punity::Screen.draw_sprite(
                    entity->transform->global_position.x,
                    entity->transform->global_position.y,
                    m_height,
                    m_width,
                    m_sprite
                    );
        }
    };
} // Punity

#endif //_PSPRITE_RENDERER_H
