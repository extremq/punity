//
// Created by god on 05.12.2022.
//

#include "GameStateManager.h"
#include "UI/UICreator.h"

namespace Game {
    GameStateManager* GameStateManager::manager = nullptr;

    void GameStateManager::on_start() {
        // Save some calls
        manager = this;

        // Config the screen pins and color
        Punity::Screen.config(HEIGHT, WIDTH, 0, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);
        Punity::Screen.background_color(0);

        // Configure the joystick pins
        Punity::Joystick.config(JOY_X, JOY_Y);
        Punity::Button.config_button(JOY_BTN);

        // Set up entities
        init_entities();

        // Begin with showing start screen
        enable_start_state();
    }

    void GameStateManager::init_entities() {
        // Set up UI
        UI = Punity::PEntity::make_entity("ui");

        // Set up start screen
        start_screen = Game::UICreator::create_start_screen();

        // Set up loading screen and digits
        load_screen = Game::UICreator::create_loading_screen();
    }

    void GameStateManager::on_update() {
        switch(state) {
            case START_SCREEN:
                // Got a button press, gotta switch to level screen
                if (Punity::Button.read_button(JOY_BTN)) {
                    disable_start_state();

                    level = 1;
                    enable_level_load_state();
                }
                break;
            case LEVEL_LOAD_SCREEN:
                break;
            case ROOM_LOAD_SCREEN:
                break;
            case GAMEPLAY:
                break;
        }
    }

    void GameStateManager::enable_start_state() {
        // Set the state
        state = START_SCREEN;

        // Show the screen
        start_screen->set_active(true);
    }

    void GameStateManager::disable_start_state() {
        // Clean up
        start_screen->set_active(false);
    }

    void GameStateManager::enable_level_load_state() {
        // Set the state
        state = LEVEL_LOAD_SCREEN;

        // Show the level load
        load_screen->set_active(true);

        for (auto digit : load_screen->get_children()) {
            // Disable the other digits
            if (digit->name != std::to_string(level)) {
                digit->set_active(false);
            }
        }
    }

    void GameStateManager::disable_level_load_state() {
        // Cleanup
        load_screen->set_active(false);
    }
} // Game