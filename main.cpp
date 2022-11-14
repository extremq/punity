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

    using namespace Punity;
    Engine.config_screen(HEIGHT, WIDTH, 0, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);
    Screen.background_color(0xacdf);

    auto* a = new PEntity;
    Engine.root_entity.add_child(a);
    a->set_name("a");
    auto* b = new PEntity;
    Engine.root_entity.add_child(b);
    b->set_name("b");
    auto* c = new PEntity;
    b->add_child(c);
    c->set_name("c");

    Screen.load_frame();
    Engine.set_framerate(60);
    Engine.start_game();
}