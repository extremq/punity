//
// Created by god on 03.12.2022.
//

#ifndef _PUISPRITERENDERER_H
#define _PUISPRITERENDERER_H

#include "punity/Components/PSpriteRenderer.h"

namespace Punity::Components {
    class PUISpriteRenderer : public PSpriteRenderer {
        // Literally the same functionality, but needs to be differentiated
        friend class PScreen;
    public:
        Utils::PVector ui_position;
    };

} // Components

#endif //_PUISPRITERENDERER_H
