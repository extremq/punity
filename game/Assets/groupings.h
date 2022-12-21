//
// Created by god on 17.12.2022.
//

#ifndef ENGINE_GROUPINGS_H
#define ENGINE_GROUPINGS_H

#include "sprites.h"
#include "sprite_layers.h"
#include "maps.h"

// Useful library for grouped things such as sprites
namespace Game::Groupings {
    extern uint16_t* const numbers[10];
    extern bool* const numbers_alpha[10];
    extern uint16_t const numbers_h[10];
    extern uint16_t const numbers_w[10];
    extern Tile* const maps[2];
}

#endif //ENGINE_GROUPINGS_H
