//
// Created by god on 17.12.2022.
//

#ifndef _CHESTBEHAVIOUR_H
#define _CHESTBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {
    // Should just compute rewards
    class ChestBehaviour : public Punity::Components::PComponent {
        void on_enable() override;
    };
} // Game

#endif //_CHESTBEHAVIOUR_H
