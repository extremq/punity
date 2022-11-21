//
// Created by god on 12.11.2022.
//

#ifndef _PSPRITE_RENDERER_H
#define _PSPRITE_RENDERER_H

#include <iostream>
#include "PComponent.h"
#include "punity/Utils/PVector.h"
#include "punity/Entity/PEntity.h"

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

        // Overload with custom offset
        void set_sprite(uint16_t const * sprite, uint16_t h, uint16_t w, uint16_t l, Punity::Utils::PVector my_offset) {
            m_sprite = sprite;
            m_height = h;
            m_width = w;
            offset = my_offset;
            layer = l;
        }

        uint16_t const* get_sprite() {
            return m_sprite;
        }

        // Need to offset so we can have the sprite's center
        // described by the entity transform
        Utils::PVector offset = {0, 0};

        // Let PScreen handle privates for efficiency
        friend class PScreen;

        uint16_t layer = 0;
        uint16_t const& height = m_height;
        uint16_t const& width = m_width;

        void on_enable() override {
            std::cout << "I'm enabled\n";
        }

        void on_disable() override {
            std::cout << "I'm disabled\n";
        }

        void on_start() override {
            std::cout << "Hello it's me\n";
        }
    };
} // Punity

#endif //_PSPRITE_RENDERER_H
