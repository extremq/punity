//
// Created by god on 12.11.2022.
//

#ifndef _PSPRITE_RENDERER_H
#define _PSPRITE_RENDERER_H

#include <iostream>
#include "PBasicSprite.h"

namespace Punity::Components {
    class PSpriteRenderer : public PBasicSprite {
        // PSpriteRenderer is simply an alias for PBasicSprite
        // I need to have it this way because dynamic casting to PBasicSprite will reduce
        // all other derived classes (such as PUI or PAnim) to PBasicSprite and will qualify
        // for a cast even though it makes no sense.
    };
} // Punity

#endif //_PSPRITE_RENDERER_H
