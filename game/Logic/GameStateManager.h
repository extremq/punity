//
// Created by god on 05.12.2022.
//

#ifndef _GAMESTATEMANAGER_H
#define _GAMESTATEMANAGER_H

#include "punity/Punity.h"
#include "game/sprites.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;
constexpr uint8_t JOY_X = 26;
constexpr uint8_t JOY_Y = 27;
constexpr uint8_t JOY_BTN = 0;

constexpr uint8_t MAX_LEVEL = 3;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

enum State {
    START_SCREEN,
    LEVEL_LOAD_SCREEN,
    ROOM_LOAD_SCREEN,
    GAMEPLAY
};

// The state manager of the game, coordinates the whole logic
// Its a component that will be attached to a standalone entity
namespace Game {
    class GameStateManager : public Punity::Components::PComponent {
    private:
        // The game begins in START_SCREEN state
        State state = START_SCREEN;

        uint8_t level = 0;
        uint8_t room = 0;

        void on_start() override;
        void on_update() override;
        void init_entities();
    public:
        // States
        void enable_start_state();
        void disable_start_state();

        void enable_level_load_state();
        void disable_level_load_state();

        static GameStateManager* manager;
        Punity::PEntity* world = nullptr, *UI = nullptr;
        Punity::PEntity* start_screen = nullptr;
        Punity::PEntity* load_screen = nullptr;
    };
} // Game

#endif /// _GAMESTATEMANAGER_H
