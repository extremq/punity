//
// Created by god on 22.12.2022.
//

#ifndef _CRATEBEHAVIOUR_H
#define _CRATEBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {

    class CrateBehaviour : public Punity::Components::PComponent {
        void on_start_collision(Punity::Components::PCollider* other) override;
    };

} // Game

#endif //_CRATEBEHAVIOUR_H
