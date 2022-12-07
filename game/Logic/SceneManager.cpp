//
// Created by god on 05.12.2022.
//

#include "SceneManager.h"
#include "SceneCreator.h"
#include "punity/Utils/PInvokable.h"
#include "game/Logic/Gameplay/GameplaySceneBehaviour.h"

namespace Game::SceneManager {
    uint8_t level = 1;
    uint8_t stage = 1;
    Scene scene = START_SCENE;

    Punity::PEntity* UI = nullptr;
    Punity::PEntity* world = nullptr;
    Punity::PEntity* gameplay_scene = nullptr;
    Punity::PEntity* start_scene = nullptr;
    Punity::PEntity* load_scene = nullptr;

    void start_manager() {
        // Config the screen pins and color
        Punity::Screen.config(HEIGHT, WIDTH, 0, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);
        Punity::Screen.background_color(0);

        // Configure the joystick pins
        Punity::Joystick.config(JOY_X, JOY_Y);
        Punity::Button.config_button(JOY_BTN);

        // Set up entities
        init_entities();

        // Load the Start scene
        switch_scene(START_SCENE);

        // Start the engine and specify framerate
        Punity::Engine.set_framerate(60);
        Punity::Engine.start_game();
    }

    void init_entities() {
        // Scenes are separated into WORLD and UI
        // UI scenes are children of UI
        // Gameplay scenes are children of WORLD

        // Set up UI
        UI = Punity::PEntity::make_entity("UI");

        // Set up world entity
        world = Punity::PEntity::make_entity("World");

        // Set up room
        gameplay_scene = Game::SceneCreator::create_gameplay_scene();
        gameplay_scene->set_parent(SceneManager::world);

        // Set up start screen
        start_scene = Game::SceneCreator::create_start_scene();
        start_scene->set_parent(SceneManager::UI);

        // Set up loading screen and digits
        load_scene = Game::SceneCreator::create_loading_scene();
        load_scene->set_parent(SceneManager::UI);
    }

    // Called from other components when wanting to switch the state/scene
    // Everything is handled here
    // This should be seen as a state machine
    void switch_scene(Scene new_scene) {
        if (scene == START_SCENE) {
            if(new_scene == LEVEL_LOAD_SCENE) {
                start_scene->set_active(false);

                // Set the state
                scene = LEVEL_LOAD_SCENE;

                // Show the level load
                load_scene->set_active(true);
            }
            else if (new_scene == START_SCENE) {
                // For consistency purposes.
                // This happens when the game starts
                start_scene->set_active(true);

                // Set the state
                scene = START_SCENE;
            }
        }
        else if (scene == LEVEL_LOAD_SCENE) {
            if (new_scene == GAMEPLAY_SCENE) {
                load_scene->set_active(false);

                // Set the state
                scene = GAMEPLAY_SCENE;

                gameplay_scene->set_active(true);
            }
        }
        else if (scene == GAMEPLAY_SCENE) {
            if (new_scene == LEVEL_LOAD_SCENE) {
                gameplay_scene->set_active(false);

                // Set the state
                scene = LEVEL_LOAD_SCENE;

                load_scene->set_active(true);
            }
            else if (new_scene == START_SCENE) {
                gameplay_scene->set_active(false);

                // Set the state
                scene = START_SCENE;

                start_scene->set_active(true);
            }
        }
    }
} // Game