//
// Created by god on 17.11.2022.
//

#ifndef _TIME_H
#define _TIME_H

#include <cstdint>
#include "punity/Engine/PEngine.fwd.h"

namespace Punity::Utils {
    class PTime {
    private:
        float m_time = 0;
        float m_delta_time = 0;
        friend class Punity::PEngine;
        PTime() = default;
    public:
        static PTime& get() {
            static PTime instance;
            return instance;
        }

        float const& time = m_time;
        float const& delta_time = m_delta_time;
    };
}// Punity


#endif //_TIME_H
