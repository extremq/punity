//
// Created by god on 11.11.2022.
//
#include <iostream>
#include "engine/Display.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

int main() {
    std::cout << "Hello world.\n";
    Display::get()->init(HEIGHT, WIDTH, TFT_CS, TFT_DC,
                         TFT_SDA, TFT_SCL, TFT_RES, 0);
    Display::get()->background_color(0x368F);
    Display::get()->load_frame();
    while(1);
}