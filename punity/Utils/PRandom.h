//
// Created by god on 22.11.2022.
//

#ifndef _PRANDOM_H
#define _PRANDOM_H

#include "pico/stdlib.h"
#include "hardware/regs/rosc.h"
#include "hardware/regs/addressmap.h"

#define MAXIMUM_UINT32 4294967295.0f

namespace Punity::Utils::PRandom {

    static float get_random(){
        uint32_t k, random = 0;
        volatile uint32_t *rnd_reg = (uint32_t *) (ROSC_BASE + ROSC_RANDOMBIT_OFFSET);
        for(k = 0 ; k < 32; k++){

            random = random << 1;
            random = random + (0x00000001 & (*rnd_reg));

        }
        return (2.0f * (random / MAXIMUM_UINT32)) - 1;
    }
}

#endif //_PRANDOM_H
