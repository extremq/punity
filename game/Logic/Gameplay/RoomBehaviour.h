//
// Created by god on 08.12.2022.
//

#ifndef _ROOMBEHAVIOUR_H
#define _ROOMBEHAVIOUR_H

#include "punity/Punity.h"
#include "game/Assets/maps.h"

namespace Game {

    class RoomBehaviour : public Punity::Components::PComponent {
    private:
        uint8_t enemy_count = 3;

        void on_enable() override;
        void on_disable() override;
        void solve_tile(uint8_t row, uint8_t column, float delay, Tile tile);
        void make_wall(int index);
        void make_crate(int index);
        Punity::Utils::PVector player_starting_position;
    public:
        // Tiles used for dictating how the world should be generated
        Tile tiles[16][16] = {EMPTY};

        // Room generation
        uint8_t get_enemy_count();
        void generate_stage();
        void disintegrate_stage();
        Punity::Utils::PVector get_player_starting_position();
    };

} // Game

#endif //_ROOMBEHAVIOUR_H
