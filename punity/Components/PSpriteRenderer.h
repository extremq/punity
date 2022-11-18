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
        void set_sprite(uint16_t const * sprite, uint16_t h, uint16_t w, uint16_t l) {
            m_sprite = sprite;
            m_height = h;
            m_width = w;
            offset = {-m_width / 2.0f, -m_height / 2.0f};
            layer = l;
        }

        // Need to offset so we can have the sprite's center
        // described by the entity transform
        Utils::PVector offset = {0, 0};

        // Let PScreen handle privates for efficiency
        friend class PScreen;

        uint16_t layer = 0;

        void on_update() override {
            Punity::Screen.draw_sprite(
                    entity->transform->global_position.x + offset.x,
                    entity->transform->global_position.y + offset.y,
                    m_height,
                    m_width,
                    m_sprite
                    );
        }
    };
} // Punity

#endif //_PSPRITE_RENDERER_H
