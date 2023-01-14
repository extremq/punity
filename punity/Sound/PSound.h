//
// Created by xnydd on 1/14/2023.
//

#ifndef _PSOUND_H
#define _PSOUND_H

#include <cstdint>
#include <hardware/gpio.h>
#include "punity/Utils/PError.h"
#include "punity/Utils/PTime.h"

namespace Punity::Sound {

    class PSound {
        bool is_initialized = false;
        PSound() = default;
        float play_until = 0.0f;
        uint8_t buzzer_pin = 0;

        // For updating
        friend class Punity::PEngine;

        void update() {
            if (Utils::PTime::get().time <= play_until) {
                // Should be playing
                gpio_put(buzzer_pin, true);
            }
            else
                gpio_put(buzzer_pin, false);
        }

    public:
        static PSound& get() {
            static PSound instance;
            return instance;
        }

        void config(uint8_t pin) {
            if (is_initialized)
                Utils::Error("Sound component already initialized.");

            is_initialized = true;
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_OUT);

            buzzer_pin = pin;
        }

        void play_beep(float time_seconds) {
            if (!is_initialized)
                Utils::Error("Sound component not initialized.");

            play_until = Utils::PTime::get().time + time_seconds;
        }
    };

} // Sound

#endif //_PSOUND_H
