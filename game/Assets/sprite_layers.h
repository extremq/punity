//
// Created by god on 08.12.2022.
//

#ifndef _SPRITE_LAYERS_H
#define _SPRITE_LAYERS_H

#include <cstdint>

namespace Game::Sprites::Layers {
    constexpr uint8_t PICKUP = 0;
    constexpr uint8_t PLAYER = 1;
    constexpr uint8_t WALL = 2;
    constexpr uint8_t CHEST = 3;
    constexpr uint8_t BULLET = 3;
    constexpr uint8_t SELECTOR = 4;

    constexpr uint8_t HUD = 1;
}

#endif //_SPRITE_LAYERS_H
