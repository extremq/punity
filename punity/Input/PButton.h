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
        bool m_configured[256] = {false};
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

        void config(uint8_t pin) {
            gpio_init(pin);
            gpio_set_dir(pin, GPIO_IN);
            gpio_pull_up(pin);
            m_configured[pin] = true;
        }

        bool read_button(uint8_t pin);
    };
}

#endif //_PBUTTON_H
