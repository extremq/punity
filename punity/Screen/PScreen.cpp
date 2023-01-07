//
// Created by god on 12.11.2022.
//

#include <hardware/gpio.h>
#include <hardware/spi.h>
#include "ST7735_defines.h"
#include "PScreen.h"
#include "punity/Utils/PError.h"

namespace Punity {
    void PScreen::config(uint16_t h,
                         uint16_t w,
                         uint8_t spi,
                         uint8_t cs,
                         uint8_t dc,
                         uint8_t sda,
                         uint8_t scl,
                         uint8_t res) {
        // Is this object initialized?
        if (m_initialized) return;
        if (w == 0 || h == 0) Punity::Utils::Error("Zero width/height screen.");

        // First time, let's set these in stone
        m_initialized = true;
        m_height = h;
        m_width = w;
        m_spi_port = spi;
        m_cs = cs;
        m_dc = dc;
        m_sda = sda;
        m_scl = scl;
        m_res = res;

        m_frame_buffer = new uint16_t[w * h];
        m_last_frame_buffer = new uint16_t[w * h];
        m_background_tile = new uint16_t[8 * 8];

        for (uint16_t i = 0; i < 8 * 8; ++i)
            m_background_tile[i] = 0;

        m_diff = new uint8_t[w * h];

        // Set buffer to white, while also setting
        // last Frame to black. We don't
        // want them to be the same otherwise we
        // can't init the first screen. (because of diff)

        for (uint16_t i = 0; i < w * h; ++i) {
            m_frame_buffer[i] = 0xffff;
            m_last_frame_buffer[i] = 0;
        }

        // Now, init the pins

        spi_init(m_spi_port == 0 ? spi0 : spi1, 20 * 1000 * 1000); // Set freq

        gpio_init(m_sda);
        gpio_init(m_scl);
        gpio_set_dir(m_sda, GPIO_OUT);
        gpio_set_dir(m_scl, GPIO_OUT);

        gpio_set_function(m_sda, GPIO_FUNC_SPI); // Init _sda
        gpio_set_function(m_scl, GPIO_FUNC_SPI); // Init scl

        gpio_init(m_dc); // Init
        gpio_set_dir(m_dc, GPIO_OUT);
        gpio_put(m_dc, false);

        gpio_init(m_cs); // Init cs
        gpio_set_dir(m_cs, GPIO_OUT);
        gpio_put(m_cs, true); // CS is active low

        gpio_init(m_res);
        gpio_set_dir(m_res, GPIO_OUT);
        gpio_put(m_res, true); // RES is active low

        init_lcd(); // And finally init the lcd.

        // Init the frame
        compute_diff();
    }

    void PScreen::compute_diff() {
        for (uint16_t i = 0; i < m_height * m_width; ++i) {
            // If the pixel is different, then diff is one there.
            m_diff[i] = (m_frame_buffer[i] != m_last_frame_buffer[i]);
            m_last_frame_buffer[i] = m_frame_buffer[i];
        }
    }

    void PScreen::draw_ui(int32_t col, int32_t row, int32_t h, int32_t w, const uint16_t *sprite, const bool *alpha) {
        // Same code but with camera at 0, 0
        // It would be better to wrap these calls to a common function
        // Shouldn't be repeating code.
        int32_t cam_far_w = m_width / 2;
        int32_t cam_near_w = -m_width / 2 - 1;
        int32_t cam_far_h = m_width / 2;
        int32_t cam_near_h = -m_width / 2 - 1;

        if (col > cam_far_w || row > cam_far_h || col + w <= cam_near_w || row + h <= cam_near_h) return;
        if (h == 0 || w == 0) Punity::Utils::Error("Zero width/height sprite.");
        if (sprite == nullptr) Punity::Utils::Error("Null sprite.");

        int32_t sprite_w = w; // Dims for sprite
        int32_t j_start = 0, i_start = 0; // Starting points for sprite

        // Clamping
        if (col < cam_near_w) {
            j_start = cam_near_w - col;
            w -= j_start;
            col = cam_near_w;
        }

        if (row < cam_near_h) {
            i_start = cam_near_h - row;
            h -= i_start;
            row = cam_near_h;
        }

        if (col + w > cam_far_w) {
            w -= col + w - cam_far_w;
        }

        if (row + h > cam_far_h) {
            h -= row + h - cam_far_h;
        }

        // Start writing
        for (int32_t y = row, i = i_start; y < row + h; ++y, ++i) {
            for (int32_t x = col, j = j_start; x < col + w; ++x, ++j) {
                // Check with alpha
                if (alpha == nullptr || alpha[j + i * sprite_w])
                    m_frame_buffer[x - cam_near_w + (y - cam_near_h) * m_width] = sprite[j + i * sprite_w];
            }
        }
    }

    void PScreen::draw_sprite(int32_t col, int32_t row, int32_t h, int32_t w, const uint16_t *sprite, const bool* alpha) {
        // Sizes are bigger than 8 bits because somebody may call 255 + 1.
        // Even though it's not good to have such a huge sprite, it's better to not let
        // the value wrap to 0 because of it being a uint8_t

        // Also, col and row are signed because I may want to offset the drawing before the screen
        // Validity checks
        int32_t cam_far_w = camera.x + m_width / 2;
        int32_t cam_near_w = camera.x - m_width / 2;
        int32_t cam_far_h = camera.y + m_height / 2;
        int32_t cam_near_h = camera.y - m_height / 2;

        if (col > cam_far_w || row > cam_far_h || col + w <= cam_near_w || row + h <= cam_near_h) return;
        if (h == 0 || w == 0) Punity::Utils::Error("Zero width/height sprite.");
        if (sprite == nullptr) Punity::Utils::Error("Null sprite.");

        int32_t sprite_w = w; // Dims for sprite
        int32_t j_start = 0, i_start = 0; // Starting points for sprite

        // Clamping
        if (col < cam_near_w) {
            j_start = cam_near_w - col;
            w -= j_start;
            col = cam_near_w;
        }

        if (row < cam_near_h) {
            i_start = cam_near_h - row;
            h -= i_start;
            row = cam_near_h;
        }

        if (col + w > cam_far_w) {
            w -= col + w - cam_far_w;
        }

        if (row + h > cam_far_h) {
            h -= row + h - cam_far_h;
        }

        // Start writing
        for (int32_t y = row, i = i_start; y < row + h; ++y, ++i) {
            for (int32_t x = col, j = j_start; x < col + w; ++x, ++j) {
                // Check with alpha
                if (alpha == nullptr || alpha[j + i * sprite_w])
                    m_frame_buffer[x - cam_near_w + (y - cam_near_h) * m_width] = sprite[j + i * sprite_w];
            }
        }
    }

    void PScreen::load_background() {
        // Traverse the frame in 8x8 tiles
        for (uint16_t frame_row = 0; frame_row < 16; ++frame_row) {
            for (uint16_t frame_column = 0; frame_column < 16; ++frame_column) {
                uint16_t start_row = frame_row * 8 * m_width;
                uint16_t start_column = frame_column * 8;
                // And get each pixel of frame
                for (uint16_t tile_row = 0; tile_row < 8; ++tile_row) {
                    for (uint16_t tile_column = 0; tile_column < 8; ++tile_column) {
                        m_frame_buffer[start_row + tile_row * m_width + start_column + tile_column] = m_background_tile[tile_row * 8 + tile_column];
                    }
                }
            }
        }
    }

    void PScreen::background_color(uint16_t color) {
        for (uint16_t i = 0; i < 64; ++i)
            m_background_tile[i] = color;
    }

    void PScreen::background_tile_8x8(const uint16_t *sprite) {
        for (uint16_t i = 0; i < 64; ++i)
            m_background_tile[i] = sprite[i];
    }

    void PScreen::set_cs_voltage(bool value) const {
        gpio_put(m_cs, value);
    }

    void PScreen::set_dc_voltage(bool value) const {
        gpio_put(m_dc, value);
    }

    void PScreen::set_res_voltage(bool value) const {
        gpio_put(m_res, value);
    }

/*
 * CS is low when we send data
 * DC selects either data or cmd
 */
    void PScreen::write_cmd(uint8_t cmd) const {
        set_dc_voltage(false);
        set_cs_voltage(false);
        write_spi(cmd);
        set_cs_voltage(true);
    }

    void PScreen::write_data(uint8_t *data, uint8_t len) const {
        set_dc_voltage(true);
        set_cs_voltage(false);
        write_spi_n(data, len);
        set_cs_voltage(true);
    }

    void PScreen::write_spi(uint8_t data) const {
        spi_write_blocking(m_spi_port == 0 ? spi0 : spi1, &data, 1);

    }

    void PScreen::write_spi_n(uint8_t *data, uint16_t n) const {
        spi_write_blocking(m_spi_port == 0 ? spi0 : spi1, data, n);
    }

/*
 * SPI displays set an address window rectangle for blitting pixels
 * Parameter1:  x0 Top left corner x coordinate
 * Parameter2:  y0 Top left corner y coordinate
 * Parameter3:  x1 Lower right corner x coordinate
 * Parameter4:  y1 Lower right corner y coordinate
 * https://en.wikipedia.org/wiki/Bit_blit
 * Credits: https://github.com/bablokb/pico-st7735/
*/
    void PScreen::set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) const {
        uint8_t buf[4];
        write_cmd(ST77XX_CASET); // Set column range
        buf[0] = X_START;
        buf[1] = x0 + X_START;
        buf[2] = X_START;
        buf[3] = x1 + X_START;
        write_data(buf, 4);

        write_cmd(ST77XX_RASET); // Set row range
        buf[0] = Y_START;
        buf[1] = y0 + Y_START;
        buf[2] = Y_START;
        buf[3] = y1 + Y_START;
        write_data(buf, 4);

        write_cmd(ST77XX_RAMWR);
    }

    void PScreen::reset() const {
        set_res_voltage(true);
        sleep_ms(10);
        set_res_voltage(false);
        sleep_ms(10);
        set_res_voltage(true);
        sleep_ms(10);
    }

    void PScreen::load_frame() {
        // Commit changes to diff and buffers
        compute_diff();

        // Color bytes
        uint8_t color[2];

        for (uint16_t y = 0; y < m_height; ++y) {
            for (uint16_t x = 0; x < m_width; ++x) {
                if (!m_diff[x + y * m_width]) continue;

                // Get high and low bytes of color
                color[0] = m_frame_buffer[x + y * m_width] >> 8;
                color[1] = m_frame_buffer[x + y * m_width];

                // Set address window of 1 pixel
                set_addr_window(x, y, x, y);
                write_data(color, 2);
            }
        }
    }

/*
 * The ugly mess. Init the screen.
 * THIS DEPENDS ON LCD. PLEASE CHANGE
 * IF YOU WANT TO ADAPT IT TO YOUR LCD
 */
    void PScreen::init_lcd() {
        uint8_t buf[16];
        write_cmd(ST77XX_SWRESET); // Software reset
        sleep_us(50);
        write_cmd(ST77XX_SLPOUT); // Out of sleep mode
        sleep_us(500);

        write_cmd(ST7735_FRMCTR1); // Frame rate control
        buf[0] = 0X01;
        buf[1] = 0X2C;
        buf[2] = 0X2D;
        write_data(buf, 3);

        write_cmd(ST7735_FRMCTR2); // Frame rate control
        write_data(buf, 3);

        write_cmd(ST7735_FRMCTR3); // Frame rate control
        write_data(buf, 3);
        sleep_us(10);

        write_cmd(ST7735_INVCTR); // diplay inversion control
        buf[0] = 0x07;
        write_data(buf, 1);

        write_cmd(ST7735_PWCTR1); // power control
        buf[0] = 0xA2;
        buf[1] = 0x02;
        buf[2] = 0x84;
        write_data(buf, 3);
        sleep_us(10);

        write_cmd(ST7735_PWCTR2); // power control
        buf[0] = 0xC5;
        write_data(buf, 1);

        write_cmd(ST7735_PWCTR3); // power control
        buf[0] = 0x0A;
        buf[1] = 0x00;
        write_data(buf, 2);

        write_cmd(ST7735_PWCTR4); // power control
        buf[0] = 0x8A;
        buf[1] = 0x2A;
        write_data(buf, 2);

        write_cmd(ST7735_PWCTR5); // power control
        buf[0] = 0x8A;
        buf[1] = 0xEE;
        write_data(buf, 2);

        write_cmd(ST7735_VMCTR1);
        buf[0] = 0x0E;
        write_data(buf, 1);
        sleep_us(10);

        write_cmd(ST77XX_MADCTL);
        buf[0] = 0xC8;
        write_data(buf, 1);

        write_cmd(ST7735_GMCTRP1); // Gamma control
        buf[0] = 0x02;
        buf[1] = 0x1c;
        buf[2] = 0x07;
        buf[3] = 0x12;
        buf[4] = 0x37;
        buf[5] = 0x32;
        buf[6] = 0x29;
        buf[7] = 0x2d;
        buf[8] = 0x29;
        buf[9] = 0x25;
        buf[10] = 0x2b;
        buf[11] = 0x39;
        buf[12] = 0x00;
        buf[13] = 0x01;
        buf[14] = 0x03;
        buf[15] = 0x10;
        write_data(buf, 16);
        sleep_us(10);

        write_cmd(ST7735_GMCTRN1);
        buf[0] = 0x03;
        buf[1] = 0x1d;
        buf[2] = 0x07;
        buf[3] = 0x06;
        buf[4] = 0x2e;
        buf[5] = 0x2c;
        buf[6] = 0x29;
        buf[7] = 0x2d;
        buf[8] = 0x2e;
        buf[9] = 0x2e;
        buf[10] = 0x37;
        buf[11] = 0x3f;
        buf[12] = 0x00;
        buf[13] = 0x00;
        buf[14] = 0x02;
        buf[15] = 0x10;
        write_data(buf, 16);
        sleep_us(10);

        write_cmd(ST77XX_CASET); // Column address set
        buf[0] = 0x00;
        buf[1] = X_START;
        buf[2] = 0x00;
        buf[3] = width + X_START - 1;
        write_data(buf, 4);

        write_cmd(ST77XX_RASET); // Row address set
        buf[1] = Y_START;
        buf[3] = height + Y_START - 1;
        write_data(buf, 4);

        write_cmd(ST77XX_COLMOD); // Select 16 bit color
        buf[0] = 0x05;
        write_data(buf, 1);

        write_cmd(ST77XX_NORON); // Normal mode
        sleep_us(10);

        write_cmd(ST77XX_RAMWR);
        sleep_us(500);

        write_cmd(ST77XX_DISPON); // Display on
        sleep_us(500);
    }
}