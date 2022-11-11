//
// Created by god on 11.11.2022.
//

#ifndef _SPRITE_H
#define _SPRITE_H

#include <cstdint>

struct Sprite {
    uint16_t buffer = nullptr;
    uint16_t width = 0;
    uint16_t height = 0;

    Sprite(uint16_t h, uint16_t w, uint16_t* buff) {
        height = h;
        width = w;
        buffer = buff;
    }
};

#endif //_SPRITE_H
