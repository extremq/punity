//
// Created by god on 08.12.2022.
//

#ifndef _ROOMBEHAVIOUR_H
#define _ROOMBEHAVIOUR_H

#include "punity/Punity.h"

enum Tile {
    EMPTY,
    WALL
};

namespace Game {

    class RoomBehaviour : public Punity::Components::PComponent {
    private:
        // Tiles used for dictating how the world should be generated
        Tile tiles[16][16] = {EMPTY};

        void on_enable() override;
        void on_disable() override;
    public:
        // Room generation
        void generate_stage();
        void disintegrate_stage();
        void solve_tile(uint8_t row, uint8_t column, float delay, Tile tile);
        void make_wall(int index);
    };

} // Game

#endif //_ROOMBEHAVIOUR_H
