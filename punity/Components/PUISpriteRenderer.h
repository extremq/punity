//
// Created by god on 03.12.2022.
//

#ifndef _PUISPRITERENDERER_H
#define _PUISPRITERENDERER_H

#include "PBasicSprite.h"

namespace Punity::Components {
    class PUISpriteRenderer : public PBasicSprite {
        // All that's needed is ui_position, describing where on the screen the sprite
        // will exist
    public:
        Utils::PVector ui_position = {0, 0};
    };

} // Components

#endif //_PUISPRITERENDERER_H
