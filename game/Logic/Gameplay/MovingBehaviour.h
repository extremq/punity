//
// Created by xnydd on 1/8/2023.
//

#ifndef _MOVINGBEHAVIOUR_H
#define _MOVINGBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {

    class MovingBehaviour : public Punity::Components::PComponent {
        Punity::Utils::PVector translation_increment;
        Punity::Utils::PVector target_position;
        bool is_translating = false;
        float end_time;

        void on_update() override;
    public:
        void translate_to(Punity::Utils::PVector target, float time);
    };

} // Game

#endif //_MOVINGBEHAVIOUR_H
