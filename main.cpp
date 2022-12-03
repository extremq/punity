//
// Created by god on 11.11.2022.
//
#include <iostream>
#include "punity/Punity.h"
#include "punity/Components/PMovement.h"
#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"
#include "punity/Components/PSpriteRenderer.h"

/* Pins on PICO */
constexpr uint8_t TFT_RES = 20;
constexpr uint8_t TFT_SDA = 19;
constexpr uint8_t TFT_SCL = 18;
constexpr uint8_t TFT_CS = 17;
constexpr uint8_t TFT_DC = 16;
constexpr uint8_t JOY_X = 26;
constexpr uint8_t JOY_Y = 27;

constexpr uint8_t WIDTH = 128;
constexpr uint8_t HEIGHT = 128;

const uint16_t x[8 * 8] = {0};
const uint16_t xx[4 * 4] = {0xacdf,0xff,0xff,0xacdf,
                            0xff,0xff,0xff,0xff,
                            0xff,0xff,0xff,0xff,
                            0xacdf,0xff,0xff,0xacdf};

const bool xxalpha[4 * 4] = {false, true, true, false,
                             true, true, true, true,
                             true, true, true, true,
                             false, true, true, false};

int main() {
    stdio_init_all();
    sleep_ms(2000);

    using namespace Punity;
    Screen.config(HEIGHT, WIDTH, 0, TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RES);
    Screen.background_color(0xacdf);
    Joystick.config(JOY_X, JOY_Y);

    auto a = PEntity::make_entity("a");
    a->add_component<Components::PMovement>();
    a->add_component<Components::PCircleCollider>()->radius = 2;
    a->get_component<Components::PCircleCollider>()->is_static = false;
    a->add_component<Components::PSpriteRenderer>()->set_sprite(xx, xxalpha, 4, 4, 0);
//    auto i = PEntity::make_entity("r");
//    i->add_component<Components::PSpriteRenderer>()->set_sprite(x, 8, 8, 0);
//    i->add_component<Components::PBoxCollider>()->width = 8;
//    i->get_component<Components::PBoxCollider>()->height = 8;
//    i->transform->set_global({20, 20});

    for (int z = 0; z < 300; ++z) {
        auto i = PEntity::make_entity("r" + std::to_string(z));
        i->add_component<Components::PSpriteRenderer>()->set_sprite(x, 8, 8, 0);
        i->add_component<Components::PBoxCollider>()->width = 8;
        i->get_component<Components::PBoxCollider>()->height = 8;

        Utils::PVector rand(Utils::PRandom::get_random() * 100, Utils::PRandom::get_random() * 100);
        i->transform->set_global(rand);
        sleep_us(5);
    }

    Engine.set_framerate(60);
    Engine.start_game();
}