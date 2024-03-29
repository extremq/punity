//
// Created by god on 06.12.2022.
//

#ifndef _STARTSCREENBEHAVIOUR_H
#define _STARTSCREENBEHAVIOUR_H

#include "game/Logic/SceneManager.h"

namespace Game {
    class StartSceneBehaviour : public Punity::Components::PComponent {
        void on_enable() override {
            Punity::Screen.background_color(0);
        }
        void on_update() override {
            // If the joystick button is pressed
            if (Punity::Button.read_button(JOY_BTN)) {
                Punity::Buzzer.play_beep(0.005);

                SceneManager::level = 1;
                SceneManager::stage = 1;
                SceneManager::switch_scene(LEVEL_LOAD_SCENE);
            }
        }
    };

} // Game

#endif //_STARTSCREENBEHAVIOUR_H
