//
// Created by god on 07.12.2022.
//

#include "PlayerMovement.h"
#include "game/Logic/SceneManager.h"

namespace Game {
    void PlayerMovement::on_update() {
        if (Punity::Button.read_button(JOY_BTN)) {
            SceneManager::level++;
            SceneManager::stage = 1;
            SceneManager::switch_scene(LEVEL_LOAD_SCENE);
        }
    }
} // Game