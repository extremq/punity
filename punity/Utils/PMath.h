//
// Created by xnydd on 1/8/2023.
//

#ifndef _PMATH_H
#define _PMATH_H

#include "PVector.h"

namespace Punity::Utils {
    float distance(Punity::Utils::PVector const& a, Punity::Utils::PVector const& b);
    Punity::Utils::PVector lerp(Punity::Utils::PVector a, Punity::Utils::PVector b, float t);
} // Utils

#endif //_PMATH_H
