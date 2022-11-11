//
// Created by god on 31.10.2022.
//

#ifndef _FRAME_H
#define _FRAME_H

#include <cstdint>

/*
 * Class for operating on Frame buffers.
 *
 * Basically, all draws will be simulated in this _buffer instead of actually
 * sending them to the lcd ram. This way, I can compute a difference matrix
 * between the current Frame and the last Frame and only send different pixels.
 */

class Frame {
private:
    uint16_t* _last_frame;
protected:
    Frame();
    ~Frame();

    uint16_t* _buffer;
    bool* _diff;
public:
    uint8_t height, width;

    void compute_diff();
    void draw_sprite(int16_t col, int16_t row, uint16_t h, uint16_t w, const uint16_t* sprite);
    void background_color(uint16_t color);

    void init_frame(uint8_t h, uint8_t w);
};


#endif //_FRAME_H
