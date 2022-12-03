//
// Created by god on 12.11.2022.
//

#include <queue>
#include "PEngine.h"
#include "punity/Punity.h"
#include "punity/Entity/PEntity.h"
#include "punity/Components/PCollider.h"

namespace Punity {
    void PEngine::set_framerate(float frame_rate) {
        if (frame_rate == 0) Punity::Utils::Error("Zero frame rate.");

        m_frame_delay_us = (uint64_t) (1.0 / frame_rate) * 1000000;
    }

    void PEngine::start_game() {
        // Game loop
        std::queue<PEntity *> to_be_destroyed;

        // Let's first report the on_start event to every entity.
        // Time does not need to be updated. It will assume t = 0s.
        for (auto entity: m_all_entities) {
            // Update the components
            entity->report_start_to_components();
        }

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

            // Sprites arranged by layer
            std::multiset<Components::PSpriteRenderer*, cmp_sprites> sprites;
            Components::PSpriteRenderer* spriteRenderer;

            std::multiset<Components::PUISpriteRenderer*, cmp_sprites> ui_sprites;
            Components::PUISpriteRenderer* ui_spriteRenderer;

            // Collider list
            std::list<Components::PCollider*> all_colliders;
            std::list<Components::PCollider*> dynamic_colliders;
            Components::PCollider* collider;

//            std::cout << "Active entities this frame:\n";
            for (auto entity: m_all_entities) {
                // Update the components
//                std::cout << " - " << entity->name << " at " << entity << '\n';

                entity->report_update_to_components();

                // But also add the sprite.
                // Should be moderately fast, but if speed is a must you could
                // use on_enable and on_disable. Of course, that comes with
                // a cost, since you must ensure it is safe and doesn't destroy
                // the multiset.
                spriteRenderer = entity->get_component<Components::PSpriteRenderer>();
                if (spriteRenderer != nullptr && spriteRenderer->is_active()) {
                    // Logarithmic
                    sprites.insert(spriteRenderer);
                }

                ui_spriteRenderer = entity->get_component<Components::PUISpriteRenderer>();
                if (ui_spriteRenderer != nullptr && ui_spriteRenderer->is_active()) {
                    // Logarithmic
                    ui_sprites.insert(ui_spriteRenderer);
                }

                // Add the collider to the collider list
                collider = entity->get_component<Components::PCollider>();
                if (collider != nullptr && collider->is_active()) {
                    all_colliders.push_back(collider);

                    // Maintain a different list of dynamic colliders
                    // for efficiency.
                    if (!collider->is_static) {
                        dynamic_colliders.push_back(collider);
                    }
                }
            }

            // Collision first, rendering second
            for (auto dynamic_collider : dynamic_colliders) {
                for (auto common_collider : all_colliders) {
                    // Don't self-compute
                    if (common_collider == dynamic_collider) continue;

                    // Solve the collision
                    bool has_collided = dynamic_collider->solve_collision(common_collider);

                    // Notify the dynamic collider first
                    Components::PCollider* collider_in_list = dynamic_collider->check_if_exists_as_collider(common_collider);

                    if (has_collided && collider_in_list == nullptr) {
                        // If this is a new collision, add it and report the event
                        dynamic_collider->add_collider(common_collider);
                        dynamic_collider->entity->report_start_collision_to_components(common_collider);

                        common_collider->add_collider(dynamic_collider);
                        common_collider->entity->report_start_collision_to_components(dynamic_collider);
                    }
                    else if (!has_collided && collider_in_list != nullptr) {
                        // If this hasn't collided BUT it exists, delete it and report the event
                        dynamic_collider->delete_collider(common_collider);
                        dynamic_collider->entity->report_end_collision_to_components(common_collider);

                        common_collider->delete_collider(dynamic_collider);
                        common_collider->entity->report_end_collision_to_components(dynamic_collider);
                    }
                }
            }

            // Now, draw the sprites!
            for (auto sprite : sprites) {
                Punity::Screen.draw_sprite(
                        sprite->entity->transform->global_position.x + sprite->offset.x,
                        sprite->entity->transform->global_position.y + sprite->offset.y,
                        sprite->height,
                        sprite->width,
                        sprite->get_sprite(),
                        sprite->get_alpha()
                        );
            }


            // Then draw the UI!
            for (auto sprite : ui_sprites) {
                std::cout << "printing a ui\n";
                Punity::Screen.draw_ui(
                        sprite->ui_position.x + sprite->offset.x,
                        sprite->ui_position.y + sprite->offset.y,
                        sprite->height,
                        sprite->width,
                        sprite->get_sprite(),
                        sprite->get_alpha()
                );
            }

            // Render the screen
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