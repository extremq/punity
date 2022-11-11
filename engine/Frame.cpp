//
// Created by god on 31.10.2022.
//

#include <cmath>
#include "Frame.h"

void Frame::init_frame(uint8_t h, uint8_t w) {
    this->height = h;
    this->width = w;
    this->_buffer = new uint16_t [w * h];
    this->_last_frame = new uint16_t [w * h];
    this->_diff = new bool [w * h];

    // Set buffer to black, while also setting
    // last Frame to some other value. We don't
    // want them to be the same otherwise we
    // can't init the first screen.

    for (uint16_t i = 0; i < w * h; ++i) {
        this->_buffer[i] = 0xffff;
        this->_last_frame[i] = 0;
    }
}

// Safely deallocate memory
Frame::~Frame() {
    delete [] this->_buffer;
    delete [] this->_last_frame;
    delete [] this->_diff;
}

// Compute difference between Frame and last_frame in the diff matrix
void Frame::compute_diff() {
    for (uint16_t i = 0; i < this->height * this->width; ++i) {
        // If the pixel is different, then diff is one there.
        this->_diff[i] = (this->_buffer[i] != this->_last_frame[i]);
        this->_last_frame[i] = this->_buffer[i];
    }
}

void Frame::background_color(uint16_t color) {
    for (uint16_t i = 0; i < this->height * this->width; ++i) {
        this->_buffer[i] = color;
    }
}

// Sizes are bigger than 8 bits because somebody may call 255 + 1.
// Even though it's not good to have such a huge sprite, it's better to not let
// the value wrap to 0 because of it being a uint8_t

// Also, col and row are signed because I may want to offset the drawing before the screen
void Frame::draw_sprite(int16_t col, int16_t row, uint16_t h, uint16_t w, const uint16_t *sprite) {
    // Validity checks
    if (col > this->width || row > this->height || col + w <= 0 || row + h <= 0) return;
    if (h == 0 || w == 0) return;

    uint16_t sprite_w = w; // Dims for sprite
    uint16_t j_start = 0, i_start = 0; // Starting points for sprite

    // Clamping
    if (col < 0) {
        j_start += -col;
        w += -col;
        col = 0;
    }

    if (row < 0) {
        i_start += -row;
        h += -row;
        row = 0;
    }

    if (col + w > this->width) {
        w = this->width - col;
    }

    if (row + h > this->height) {
        h = this->height - row;
    }

    for (uint16_t y = row, i = i_start; y < row + h; ++y, ++i) {
        for (uint16_t x = col, j = j_start; x < col + w; ++x, ++j) {
            this->_buffer[x + y * this->height] = sprite[j + i * sprite_w];
        }
    }
}

Frame::Frame() {
    this->width = 0;
    this->height = 0;
    this->_buffer = nullptr;
    this->_last_frame = nullptr;
    this->_diff = nullptr;
}

