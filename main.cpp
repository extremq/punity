//
// Created by god on 11.11.2022.
//
#include <iostream>
#include "punity/Punity.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

int main() {
    stdio_init_all();
    sleep_ms(2000);

    Punity::Engine.config_screen(HEIGHT, WIDTH, 0, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);
    Punity::Screen.background_color(0xacdf);
    Punity::Screen.load_frame();
    Punity::Engine.set_framerate(1);
    Punity::Engine.start_game();
}