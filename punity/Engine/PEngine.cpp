//
// Created by god on 12.11.2022.
//

#include "PEngine.h"
#include "punity/Punity.h"

namespace Punity {
    void PEngine::config_screen(uint16_t h, uint16_t w, uint8_t spi, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl,
                                uint8_t res) {
        Punity::Screen.config(h, w, spi, cs, dc, sda, scl, res);
    }

    void PEngine::set_framerate(uint8_t frame_rate) {
        if (frame_rate == 0) Punity::Error("Zero frame rate.");

        m_frame_delay_us = (uint64_t) (1.0 / frame_rate) * 1000000;
    }

    void PEngine::start_game() {
        // Game loop
        while (true) {
            uint64_t frame_start_time = time_us_64();

            root_entity.propagate_update();

            // Sleep the remaining frame time
            uint64_t time_difference = time_us_64() - frame_start_time;
            if (time_difference < m_frame_delay_us) {
                sleep_us(m_frame_delay_us - time_difference);
            }
        }
    }
}