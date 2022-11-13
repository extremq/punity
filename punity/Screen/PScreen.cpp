//
// Created by god on 12.11.2022.
//

#include <hardware/gpio.h>
#include <hardware/spi.h>
#include "ST7735_defines.h"
#include "PScreen.h"
#include "punity/Punity.h"

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
        if (w == 0 || h == 0) Punity::Error("Zero width/height screen.");

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
    }

    void PScreen::compute_diff() {
        for (uint16_t i = 0; i < m_height * m_width; ++i) {
            // If the pixel is different, then diff is one there.
            m_diff[i] = (m_frame_buffer[i] != m_last_frame_buffer[i]);
            m_last_frame_buffer[i] = m_frame_buffer[i];
        }
    }

    void PScreen::draw_sprite(int16_t col, int16_t row, uint16_t h, uint16_t w, const uint16_t *sprite) {
        // Sizes are bigger than 8 bits because somebody may call 255 + 1.
        // Even though it's not good to have such a huge sprite, it's better to not let
        // the value wrap to 0 because of it being a uint8_t

        // Also, col and row are signed because I may want to offset the drawing before the screen
        // Validity checks
        if (col > m_width || row > m_height || col + w <= 0 || row + h <= 0) return;
        if (h == 0 || w == 0) Punity::Error("Zero width/height sprite.");

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

        if (col + w > m_width) {
            w = m_width - col;
        }

        if (row + h > m_height) {
            h = m_height - row;
        }

        // Start writing
        for (uint16_t y = row, i = i_start; y < row + h; ++y, ++i) {
            for (uint16_t x = col, j = j_start; x < col + w; ++x, ++j) {
                m_frame_buffer[x + y * m_height] = sprite[j + i * sprite_w];
            }
        }
    }

    void PScreen::background_color(uint16_t color) {
        for (uint16_t i = 0; i < m_height * m_width; ++i) {
            m_frame_buffer[i] = color;
        }
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