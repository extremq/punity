//
// Created by god on 07.12.2022.
//

#ifndef _PLAYERMOVEMENT_H
#define _PLAYERMOVEMENT_H

#include "punity/Punity.h"

namespace Game {

    class PlayerMovement : public Punity::Components::PComponent {
        void on_update() override;
    };

} // Game

#endif //_PLAYERMOVEMENT_H
