//
// Created by god on 12.11.2022.
//

#include <queue>
#include "PEngine.h"
#include "punity/Punity.h"

namespace Punity {
    void PEngine::set_framerate(float frame_rate) {
        if (frame_rate == 0) Punity::Error("Zero frame rate.");

        m_frame_delay_us = (uint64_t) (1.0 / frame_rate) * 1000000;
    }

    void PEngine::start_game() {
        // Game loop
        std::queue<PEntity *> to_be_destroyed;
        // TODO add onStart, onDestroy
        while (true) {
            uint64_t frame_start_time = time_us_64();

            // Update Time.h util
            update_time(frame_start_time);

            // Any deletion is committed only on next frame
            for (auto it = m_all_entities.begin(); it != m_all_entities.end(); ++it) {
                if ((*it)->m_is_destroyed || !(*it)->m_is_active) {
                    if ((*it)->m_is_destroyed) {
                        // Delete the entity, but don't use delete yet.
                        // Instead, add it to a queue.
                        // Why? Since inside an on_destroy() event somebody can
                        // create more stuff.
                        to_be_destroyed.push(*it);
                        (*it)->report_destroy_to_components();
                    } else {
                        // Disable the entity.
                        (*it)->report_disable_to_components();
                    }

                    // Reached the end, don't care to save
                    if ((it != m_all_entities.end()) && (it == --m_all_entities.end())) {
                        m_all_entities.pop_back();
                        break;
                    }

                    // Swap with end and pop end.
                    auto last = m_all_entities.back();
                    m_all_entities.pop_back();

                    *it = last;
                    --it;
                }
            }

            // Now, finally, we can safely delete
            // and be assured no weird stuff happens
            while (!to_be_destroyed.empty()) {
                delete to_be_destroyed.front();
                to_be_destroyed.pop();
            }

            Punity::Screen.load_background();
            // No particular order
            // Notice that I don't do any particular checks.
            // That means inactive and destroyed objects are still called
            // However, that only happens if in this frame they were committed
            // Otherwise, the next frame will remove them.
//            std::cout << "Active entities this frame:\n";
            for (auto entity: m_all_entities) {
                // Update the components
//                std::cout << " - " << entity->name << " at " << entity << '\n';
                entity->report_update_to_components();
            }

            Punity::Screen.load_frame();
            // Sleep the remaining frame time
            uint64_t time_difference = time_us_64() - frame_start_time;
            if (time_difference < m_frame_delay_us) {
                sleep_us(m_frame_delay_us - time_difference);
            }
        }
    }

    void PEngine::register_entity(PEntity* entity) {
        entity->report_enable_to_components();
        std::cout << "registering " << entity->name << '\n';
        m_all_entities.push_front(entity);
    }

    void PEngine::update_time(uint64_t raw_time) {
        float raw_time_seconds = raw_time / 1000000.0f;
        Punity::Time.m_delta_time = raw_time_seconds - Punity::Time.m_time;
        Punity::Time.m_time = raw_time_seconds;
    }

    PEngine::PEngine() {
        root_entity = new PEntity("__Root");
    }
}