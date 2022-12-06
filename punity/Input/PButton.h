//
// Created by god on 05.12.2022.
//

#ifndef _PBUTTON_H
#define _PBUTTON_H

#include <cstdint>
#include <hardware/gpio.h>

namespace Punity::Input {
    class PButton {
    private:
        // Allow one single init, basically a fake read-only
        // This is why I need a class, as well
        bool m_initialized = false;
        PButton() = default;
    public:
        // Return singleton instance
        static PButton& get() {
            static PButton instance;
            return instance;
        }

        void config_button(uint8_t pin) {
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            gpio_pull_up(pin);
        }

        bool read_button(uint8_t pin) {
            return !gpio_get(pin);
        }
    };
}

#endif //_PBUTTON_H
