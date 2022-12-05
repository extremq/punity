//
// Created by god on 05.12.2022.
//

#ifndef _PBASICSPRITE_H
#define _PBASICSPRITE_H
#include "PComponent.h"
#include "punity/Utils/PVector.h"
#include "punity/Entity/PEntity.h"

namespace Punity::Components {
    class PBasicSprite : public PComponent {
    protected:
        // Pointer to const
        // Shared memory, of course!
        // All modifiers are applied at draw-stage
        uint16_t const * m_sprite = nullptr;
        uint16_t m_height = 0;
        uint16_t m_width = 0;
        bool const * m_alpha = nullptr;

    public:
        void set_sprite(uint16_t const * sprite, uint16_t h, uint16_t w, uint16_t l) {
            m_sprite = sprite;
            m_height = h;
            m_width = w;
            offset = {-m_width / 2.0f, -m_height / 2.0f};
            layer = l;
        }

        void set_sprite(uint16_t const * sprite, bool const* alpha, uint16_t h, uint16_t w, uint16_t l) {
            m_sprite = sprite;
            m_alpha = alpha;
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

        bool const* get_alpha() {
            return m_alpha;
        }

        // Need to offset so we can have the sprite's center
        // described by the entity transform
        Utils::PVector offset = {0, 0};

        uint16_t layer = 0;
        uint16_t const& height = m_height;
        uint16_t const& width = m_width;
    };

} // Components

#endif //_PBASICSPRITE_H
