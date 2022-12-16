//
// Created by god on 06.12.2022.
//
#include "PRandom.h"

#include "pico/stdlib.h"
#include "hardware/regs/rosc.h"
#include "hardware/regs/addressmap.h"

#define MAXIMUM_UINT32 4294967295.0f

namespace Punity::Utils {
    float random(){
        // [0, 1]
        uint32_t k, random_number = 0;
        volatile uint32_t *rnd_reg = (uint32_t *) (ROSC_BASE + ROSC_RANDOMBIT_OFFSET);
        for(k = 0 ; k < 32; k++){

            random_number = random_number << 1;
            random_number = random_number + (0x00000001 & (*rnd_reg));
        }
        return (random_number / MAXIMUM_UINT32);
    }
    float random_minus_plus(){
        // [-1, 1]
        uint32_t k, random_number = 0;
        volatile uint32_t *rnd_reg = (uint32_t *) (ROSC_BASE + ROSC_RANDOMBIT_OFFSET);
        for(k = 0 ; k < 32; k++){

            random_number = random_number << 1;
            random_number = random_number + (0x00000001 & (*rnd_reg));
        }
        return 2.0f * (random_number / MAXIMUM_UINT32) - 1;
    }
}