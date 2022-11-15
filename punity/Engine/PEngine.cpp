//
// Created by god on 12.11.2022.
//

#include "PEngine.h"
#include "punity/Punity.h"

namespace Punity {
    void PEngine::config_screen(uint16_t h, uint16_t w, uint8_t spi, uint8_t cs, uint8_t dc, uint8_t sda, uint8_t scl,
                                uint8_t res) {
        Punity::Screen.config(h, w, spi, cs, dc, sda, scl, res);
    }

    void PEngine::set_framerate(float frame_rate) {
        if (frame_rate == 0) Punity::Error("Zero frame rate.");

        m_frame_delay_us = (uint64_t) (1.0 / frame_rate) * 1000000;
    }

    void PEngine::start_game() {
        // Game loop
        while (true) {
            uint64_t frame_start_time = time_us_64();

            // Any deletion is commited only on next frame
            for (auto it = m_all_entities.begin(); it != m_all_entities.end(); ++it) {
                if ((*it)->m_is_destroyed) {
                    // delete the entity
                    // any entity should be NEW
                    delete *it;

                    // Swap with end and pop end.
                    auto last = m_all_entities.back();
                    m_all_entities.pop_back();

                    // Maybe we popped the end
                    if (it != m_all_entities.end())
                        *it = last;

                    --it;
                }
            }

            // No particular order
            for (auto entity : m_all_entities) {
                // Skip over disabled or destroyed objects
                if (!entity->m_is_active || entity->m_is_destroyed) continue;

                // Update the components
                entity->on_update();
            }

            // Sleep the remaining frame time
            uint64_t time_difference = time_us_64() - frame_start_time;
            if (time_difference < m_frame_delay_us) {
                sleep_us(m_frame_delay_us - time_difference);
            }
        }
    }

    void PEngine::register_entity(PEntity *entity) {
        m_all_entities.push_front(entity);
    }
}