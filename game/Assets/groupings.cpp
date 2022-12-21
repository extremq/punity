//
// Created by god on 17.12.2022.
//

#include "groupings.h"

namespace Game::Groupings {
    uint16_t* const numbers[10] = {
            (uint16_t *) Game::Sprites::zero,
            (uint16_t *) Game::Sprites::one,
            (uint16_t *) Game::Sprites::two,
            (uint16_t *) Game::Sprites::three,
            (uint16_t *) Game::Sprites::four,
            (uint16_t *) Game::Sprites::five,
            (uint16_t *) Game::Sprites::six,
            (uint16_t *) Game::Sprites::seven,
            (uint16_t *) Game::Sprites::eight,
            (uint16_t *) Game::Sprites::nine
    };
    bool* const numbers_alpha[10] = {
            (bool *) Game::Sprites::zero_alpha,
            (bool *) Game::Sprites::one_alpha,
            (bool *) Game::Sprites::two_alpha,
            (bool *) Game::Sprites::three_alpha,
            (bool *) Game::Sprites::four_alpha,
            (bool *) Game::Sprites::five_alpha,
            (bool *) Game::Sprites::six_alpha,
            (bool *) Game::Sprites::seven_alpha,
            (bool *) Game::Sprites::eight_alpha,
            (bool *) Game::Sprites::nine_alpha
    };
    uint16_t const numbers_h[10] = {
            (uint16_t) Game::Sprites::zero_h,
            (uint16_t) Game::Sprites::one_h,
            (uint16_t) Game::Sprites::two_h,
            (uint16_t) Game::Sprites::three_h,
            (uint16_t) Game::Sprites::four_h,
            (uint16_t) Game::Sprites::five_h,
            (uint16_t) Game::Sprites::six_h,
            (uint16_t) Game::Sprites::seven_h,
            (uint16_t) Game::Sprites::eight_h,
            (uint16_t) Game::Sprites::nine_h
    };
    uint16_t const numbers_w[10] = {
            (uint16_t) Game::Sprites::zero_w,
            (uint16_t) Game::Sprites::one_w,
            (uint16_t) Game::Sprites::two_w,
            (uint16_t) Game::Sprites::three_w,
            (uint16_t) Game::Sprites::four_w,
            (uint16_t) Game::Sprites::five_w,
            (uint16_t) Game::Sprites::six_w,
            (uint16_t) Game::Sprites::seven_w,
            (uint16_t) Game::Sprites::eight_w,
            (uint16_t) Game::Sprites::nine_w
    };
    Tile* const maps[1] = {
            (Tile*) Game::Maps::map1
    };
}
