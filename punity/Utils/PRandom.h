//
// Created by god on 22.11.2022.
//

#ifndef _PRANDOM_H
#define _PRANDOM_H

// Simple rng based on ring oscillator
namespace Punity::Utils {
    float random();
    float random(float a, float b);
}

#endif //_PRANDOM_H
