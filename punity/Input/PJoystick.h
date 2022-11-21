//
// Created by god on 17.11.2022.
//

#ifndef _PJOYSTICK_H
#define _PJOYSTICK_H

#include <cstdint>
#include "hardware/adc.h"

namespace Punity::Input {
    class PJoystick {
    private:

        // Allow one single init, basically a fake read-only
        bool m_initialized = false;

        PJoystick() = default;
        const uint16_t max_value = 4095;
        const uint16_t mid_point = 4095 / 2;
        const float mid_point_precise = max_value / 2.0;
    public:
        // Init the analog to digital converter pins
        void config(uint8_t xpin, uint8_t ypin) {
            if (m_initialized) return;

            m_initialized = true;
            adc_init();
            adc_gpio_init(xpin);
            adc_gpio_init(ypin);
        }

        uint16_t get_x() {
            adc_select_input(0);
            return adc_read();
        }

        uint16_t get_y() {
            adc_select_input(1);
            return adc_read();
        }

        // Return singleton instance
        static PJoystick& get() {
            static PJoystick instance;
            return instance;
        }

        uint16_t get_max_value() {
            return this->max_value;
        }

        // Returns -1, 0 or 1 depending on direction on that axis
        int8_t get_x_direction() {
            adc_select_input(0);
            uint16_t raw_x = adc_read();
            if (raw_x < mid_point - 100) return -1;
            if (raw_x < mid_point + 100) return 0;
            return 1;
        }

        int8_t get_y_direction() {
            adc_select_input(1);
            uint16_t raw_y = adc_read();
            if (raw_y < mid_point - 100) return -1;
            if (raw_y < mid_point + 100) return 0;
            return 1;
        }

        // Return [-1, 1] depending on direction
        // All these computations should be optimised by the compiler since they are const
        float get_x_direction_precise() {
            adc_select_input(0);
            double raw_x = adc_read();
            if (raw_x < 100) return -1;
            if (raw_x < mid_point_precise - 100) return - 1.0 + (raw_x - 100) / (mid_point_precise - 100);
            if (raw_x < mid_point_precise + 100) return 0.0;
            if (raw_x < max_value - 100)
                return (raw_x - (mid_point_precise + 100)) / (max_value - mid_point_precise);
            return 1.0;
        }

        float get_y_direction_precise() {
            adc_select_input(1);
            double raw_y = adc_read();
            if (raw_y < 100) return -1;
            if (raw_y < mid_point_precise - 100) return - 1.0 + (raw_y - 100) / (mid_point_precise - 100);
            if (raw_y < mid_point_precise + 100) return 0.0;
            if (raw_y < max_value - 100)
                return (raw_y - (mid_point_precise + 100)) / (max_value - mid_point_precise);
            return 1.0;
        }
    };
} // Utils

#endif //_PJOYSTICK_H
