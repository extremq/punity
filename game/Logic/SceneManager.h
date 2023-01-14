//
// Created by god on 05.12.2022.
//

#ifndef _GAMESTATEMANAGER_H
#define _GAMESTATEMANAGER_H

#include "punity/Punity.h"
#include "game/Assets/sprites.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;
constexpr uint8_t JOY_X = 26;
constexpr uint8_t JOY_Y = 27;
constexpr uint8_t JOY_BTN = 0;
constexpr uint8_t ACTION_BTN = 1;
constexpr uint8_t BUZZ_PIN = 11;

constexpr uint8_t MAX_LEVEL = 3;
constexpr uint8_t MAX_STAGE = 3;
constexpr uint8_t MAX_WAVE = 2;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

enum Scene {
    START_SCENE,
    LEVEL_LOAD_SCENE,
    GAMEPLAY_SCENE
};

// Scenes in unity represent different worlds.
// I emulate this by making parent entities which
// will contain all elements in such stage.
// Setting the entities active/inactive will seem
// like we are switching stages
namespace Game::SceneManager {
    extern Scene scene;
    extern uint8_t level;
    extern uint8_t stage;

    // Entities in charge of "scenes"
    // Unity has scenes, but I don't. :]
    extern Punity::PEntity* UI;
    extern Punity::PEntity* world;
    extern Punity::PEntity* gameplay_scene;
    extern Punity::PEntity* start_scene;
    extern Punity::PEntity* load_scene;

    void start_manager();
    void init_entities();
    void reset_progress();
    void switch_scene(Scene new_scene);
} // Game

#endif /// _GAMESTATEMANAGER_H
