//
// Created by god on 14.11.2022.
//

#ifndef _PSPRITE_H
#define _PSPRITE_H

#include <cstdint>

namespace Punity::Utils {
    class PSprite {
    private:
        // Array of colors
        uint16_t* m_sprite_buffer = nullptr;
        uint8_t m_height = 0, m_width = 0;
    public:
        // Public read-only vars
        uint8_t const& height = m_height;
        uint8_t const& width = m_width;
        uint16_t const * const & buffer = m_sprite_buffer;

        ~PSprite() {
            delete[] m_sprite_buffer;
        }

        // Setup
        PSprite(uint16_t* sprite_buffer, uint8_t height, uint8_t width) :
            m_sprite_buffer(sprite_buffer), m_height(height), m_width(width) {};
    };

} // Punity

#endif //_PSPRITE_H
