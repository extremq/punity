//
// Created by god on 05.12.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include "game/Logic/GameStateManager.h"

enum Tile {
    EMPTY,
    WALL
};

constexpr uint8_t WALL_LAYER = 1;

namespace Game {

    // Handles gameplay mostly, since it's all contained in rooms
    class Room : public Punity::Components::PComponent {
    private:
        uint8_t counter_x = 0, counter_y = 0;

        void on_update() override;
        void on_enable() override;
        void on_disable() override;
    public:
        // Tiles used for dictating how the world should be generated
        Tile tiles[16][16] = {EMPTY};

        // Player entity
        Punity::PEntity* player = nullptr;

        void setup_level();

        void solve_tile();
        void make_wall(int index);

        // Room generation
        void generate_stage();
        void disintegrate_stage();
    };

} // Game

#endif //_ROOM_H
