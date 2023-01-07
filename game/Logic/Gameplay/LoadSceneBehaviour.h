//
// Created by god on 06.12.2022.
//

#ifndef _DIGITSETTER_H
#define _DIGITSETTER_H

#include "game/Logic/SceneManager.h"
#include "punity/Utils/PInvokable.h"

constexpr float DELAY_TO_GAMEPLAY = 3.0f;

namespace Game {
    class LoadSceneBehaviour : public Punity::Components::PComponent {
        void on_enable() override {
            Punity::Screen.background_color(0);

            // Disable the unworthy children
            for (auto digit : get_entity()->get_children()) {
                if (digit->get_name() != std::to_string(SceneManager::level)) {
                    digit->set_active(false);
                }
                else {
                    digit->set_active(true);
                }
            }

            // Load the next scene
            new Punity::Utils::PInvokable<LoadSceneBehaviour>(
                    &LoadSceneBehaviour::switch_scene_wrapper,
                    this,
                    DELAY_TO_GAMEPLAY,
                    get_entity()->get_id());
        }

        void switch_scene_wrapper() {
            SceneManager::switch_scene(GAMEPLAY_SCENE);
        }
    };
}

#endif //_DIGITSETTER_H
