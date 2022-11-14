//
// Created by god on 12.11.2022.
//

#ifndef _ENGINE_H
#define _ENGINE_H

#include "punity/Entity/PEntity.h"

#include <cstdint>
namespace Punity {
    class PEngine {
    private:
        PEngine() = default;

        // In microseconds (1e^-6 sec)
        uint64_t m_frame_delay_us = 16666; // Assume 60 fps
    public:
        // Prohibit copying.
        PEngine(const PEngine &) = delete;

        PEngine &operator=(const PEngine &) = delete;

        static PEngine &get() {
            // https://stackoverflow.com/questions/13047526/difference-between-singleton-implemention-using-pointer-and-using-static-object
            // Good read about singletons
            static PEngine m_instance;
            return m_instance;
        };

        // Config is private but friend to Engine.
        void config_screen(uint16_t h,
                           uint16_t w,
                           uint8_t spi,
                           uint8_t cs,
                           uint8_t dc,
                           uint8_t sda,
                           uint8_t scl,
                           uint8_t res);

        // Sets... the framerate.
        void set_framerate(uint8_t);

        void start_game();

        // Root Entity, head of the Entity Tree
        // Not a pointer since it's always present.
        PEntity root_entity;
    };
}

#endif //_ENGINE_H
