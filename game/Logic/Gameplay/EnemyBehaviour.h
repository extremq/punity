//
// Created by god on 12.12.2022.
//

#ifndef _ENEMYBEHAVIOUR_H
#define _ENEMYBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {

    class EnemyBehaviour : public Punity::Components::PComponent {
        void on_start_collision(Punity::Components::PCollider* other) override;
    };

} // Game

#endif //_ENEMYBEHAVIOUR_H
