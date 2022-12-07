//
// Created by god on 05.12.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include "game/Logic/SceneManager.h"

enum Tile {
    EMPTY,
    WALL
};

constexpr uint8_t WALL_LAYER = 1;
constexpr float PLAYER_CREATION_DELAY_SECONDS = 1.0f;
constexpr float ENEMY_CREATION_DELAY_SECONDS = 2.0f;

namespace Game {

    // Handles gameplay mostly, since it's all contained in rooms
    // Also a state machine.
    class GameplaySceneBehaviour : public Punity::Components::PComponent {
    private:
        // Grouping entities
        Punity::PEntity* room = nullptr;
        Punity::PEntity* enemies = nullptr;

        // Player entity
        Punity::PEntity* player = nullptr;

        uint8_t row_counter = 0, column_counter = 0;
        bool is_fighting = false;

        void on_update() override;
        void on_enable() override;
        // Tiles used for dictating how the world should be generated
        Tile tiles[16][16] = {EMPTY};

        // States
        void setup_stage();
        void cleanup_stage();
        void show_chest();
        void show_player();
        void make_enemies();
        void make_wall(int index);

        // Room generation
        void generate_stage();
        void solve_tile(uint8_t row, uint8_t column, float delay, Tile tile);
        void disintegrate_stage();
    public:
    };

} // Game

#endif //_ROOM_H
