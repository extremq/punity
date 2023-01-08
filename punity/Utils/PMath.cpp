//
// Created by xnydd on 1/8/2023.
//

#include "PMath.h"

namespace Punity::Utils {
    float distance(const PVector &a, const PVector &b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    Punity::Utils::PVector lerp(Punity::Utils::PVector a, Punity::Utils::PVector b, float t)
    {
        Punity::Utils::PVector interpolated;
        // Simple LERP function
        interpolated.x = a.x * (1.0f - t) + (b.x * t);
        interpolated.y = a.y * (1.0f - t) + (b.y * t);

        return interpolated;
    }
} // Utils