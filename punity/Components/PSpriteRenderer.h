//
// Created by god on 12.11.2022.
//

#ifndef _PSPRITE_RENDERER_H
#define _PSPRITE_RENDERER_H

#include "PComponent.h"
#include "punity/Utils/PSprite.h"

namespace Punity::Components {
    class PSpriteRenderer : public PComponent {
    private:
        Punity::Utils::PSprite m_sprite;
    public:
        // Public read-only
        Punity::Utils::PSprite const& sprite = m_sprite;

        void set_sprite(Punity::Utils::PSprite const& new_sprite) {

        }
    };
} // Punity

#endif //_PSPRITE_H
