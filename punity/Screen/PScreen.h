//
// Created by god on 12.11.2022.
//

#ifndef _SCREEN_H
#define _SCREEN_H

#include <cstdint>
#include "punity/Engine/PEngine.fwd.h"

namespace Punity {
    class PScreen {
    private:
        PScreen() = default;

        uint16_t m_bg_color = 0x0;

        // Allow one single init, basically a fake read-only
        bool m_initialized = false;

        uint16_t m_height = 0;
        uint16_t m_width = 0;

        // Pins on PCB
        uint8_t m_spi_port = 0,
                m_cs = 0,
                m_dc = 0,
                m_sda = 0,
                m_scl = 0,
                m_res = 0;

        uint16_t* m_frame_buffer = nullptr;
        uint16_t* m_last_frame_buffer = nullptr;
        uint8_t* m_diff = nullptr;

        void set_cs_voltage(bool value) const; /* Setters */
        void set_dc_voltage(bool value) const;
        void set_res_voltage(bool value) const;

        void write_cmd(uint8_t cmd) const; /* Write abstracts */
        void write_data(uint8_t* data, uint8_t len) const;

        void write_spi(uint8_t data) const; /* Spi writing */
        void write_spi_n(uint8_t* data, uint16_t n) const;

        void set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) const;
        void reset() const;
        void init_lcd();

        friend class PEngine;

        void load_background();
        void load_frame();
    public:
        // Configures the privates but has effect only once
        void config(uint16_t h,
                    uint16_t w,
                    uint8_t spi,
                    uint8_t cs,
                    uint8_t dc,
                    uint8_t sda,
                    uint8_t scl,
                    uint8_t res);

        // Prohibit copying.
        PScreen(const PScreen&) = delete;
        PScreen& operator=(const PScreen&) = delete;

        static PScreen& get() {
            static PScreen m_instance;
            return m_instance;
        }

        // Public read-only access
        uint16_t const& height = m_height;
        uint16_t const& width = m_width;

        void draw_sprite(int16_t col, int16_t row, uint16_t h, uint16_t w, const uint16_t* sprite);
        void background_color(uint16_t color);
        void compute_diff();
    };
}


#endif //_SCREEN_H
