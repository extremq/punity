//
// Created by god on 30.10.2022.
//

#ifndef _ST7735_H
#define _ST7735_H

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "Frame.h"
#include "ST7735_defines.h"

/*
 * Display.h contains all that's needed for displaying the game.
 * It is an extension of a frame. The frame only contains buffers
 * and matrix operations on that buffer, while Display.h takes care
 * of communicating with the ST7735 Controller
 *
 * I choose to inherit Frame since there are multiple but similar types
 * of display controllers and the Frame is common but the display init
 * is different, so you could create multiple types of Display instead of this one.
 */

class Display : public Frame {
private:
    uint8_t _spi_port;
    uint8_t _cs, _dc, _sda, _scl, _res; /* Pins on PCB */

    void init_pins(); /* Init functions */
    void init_lcd();

    void set_cs_voltage(bool value); /* Setters */
    void set_dc_voltage(bool value);
    void set_res_voltage(bool value);

    void write_cmd(uint8_t cmd); /* Write abstracts */
    void write_data(uint8_t* data, uint8_t len);

    void write_spi(uint8_t data); /* Spi writing */
    void write_spi_n(uint8_t* data, uint16_t n);

    void set_addr_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void reset();

    Display() {
        this->_cs = 0;
        this->_dc = 0;
        this->_res = 0;
        this->_spi_port = 0;
        this->_sda = 0;
        this->_scl = 0;
    }

    Display(const Display&);
    Display& operator=(const Display&);
public:
    void load_frame();

    static Display& get() {
        // https://stackoverflow.com/questions/13047526/difference-between-singleton-implemention-using-pointer-and-using-static-object
        // Good read about singletons
        static Display _instance;
        return _instance;
    }
    // These should only be used by GameEngine
    void init(uint8_t w, uint8_t h, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl, uint8_t res, uint8_t spi_port);

    friend class GameEngine;
};


#endif //_ST7735_H
