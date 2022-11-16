//
// Created by god on 11.11.2022.
//
#include <iostream>
#include "punity/Punity.h"
#include "punity/Components/testComponent.h"

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

    std::cout << sizeof(PEntity) << '\n';
    auto a = new PEntity("a");
    auto b = new PEntity("b");
    auto c = new PEntity("c");
    auto d = new PEntity("d");
    d->set_parent(b);
    c->set_parent(b);

    auto test = new Components::testComponent();
    auto c1 = new PEntity("c1");
    auto c2 = new PEntity("c2");
    auto c3 = new PEntity("c3");
    auto c4 = new PEntity("c4");
    c3->add_component(test);
    c1->set_parent(d);
    c2->set_parent(d);
    c3->set_parent(c1);
    c4->set_parent(c3);

    Screen.load_frame();
    Engine.set_framerate(0.5);
    Engine.start_game();
}