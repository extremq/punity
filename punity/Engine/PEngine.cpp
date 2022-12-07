//
// Created by god on 12.11.2022.
//

#include <queue>
#include "PEngine.h"
#include "punity/Punity.h"
#include "punity/Entity/PEntity.h"
#include "punity/Components/PCollider.h"
#include "punity/Utils/PInvokable.h"

namespace Punity {
    void PEngine::set_framerate(float frame_rate) {
        if (frame_rate == 0) Punity::Utils::Error("Zero frame rate.");

        m_frame_delay_us = (1.0 / frame_rate) * 1000000;
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

        // Sprites arranged by layer
        std::multiset<Components::PSpriteRenderer*, cmp_sprites> sprites;
        Components::PSpriteRenderer* spriteRenderer;

        std::multiset<Components::PUISpriteRenderer*, cmp_ui_sprites> ui_sprites;
        Components::PUISpriteRenderer* ui_spriteRenderer;

        // Collider list
        std::list<Components::PCollider*> all_colliders;
        std::list<Components::PCollider*> dynamic_colliders;
        Components::PCollider* collider;

        /*
         * ORDER OF EXECUTION:
         *
         * First, check which entities are disabled/destroyed and remove them from the active entities list
         * Then, safely delete the destroyed entities
         *
         * New frame starts here
         * Load the background
         * Loop through all entities and update them while also collecting colliders and sprites
         * Solve Invokers
         * Compute collisions
         * Draw sprites
         * Send the frame
         * Sleep the remaining time and repeat
         */
        while (true) {
            uint64_t frame_start_time = time_us_64();

            // Update Time.h util
            update_time(frame_start_time);

            // Any deletion is committed only on next frame
            for (auto it = m_all_entities.begin(); it != m_all_entities.end(); ++it) {
                if ((*it)->m_is_destroyed || !(*it)->m_globally_active || !(*it)->m_self_active) {
                    if ((*it)->m_is_destroyed) {
                        // Delete the entity, but don't use delete yet.
                        // Instead, add it to a queue.
                        // Why? Since inside an on_destroy() event somebody can
                        // create more stuff.
                        to_be_destroyed.push(*it);
                        (*it)->report_destroy_to_components();
                    } else {
                        // Disable the entity.
                        std::cout << "Disabled " << (*it)->get_name() << '\n';
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
                // Remove reference from parent
                if (to_be_destroyed.front()->get_parent() != nullptr) {
                    to_be_destroyed.front()->get_parent()->remove_child_entity(to_be_destroyed.front());
                }
                for (auto child : to_be_destroyed.front()->get_children()) {
                    // mark parents of destroyed child as nullptr
                    child->m_parent_entity = nullptr;
                }

                // Also remove invokers with this entity id
                for (auto it = m_invokers.begin(); it != m_invokers.end(); ++it) {
                    // If execution time has reached its point, lets invoke the function
                    if ((*it)->get_entity_id() == to_be_destroyed.front()->get_id()) {
                        delete *it;
                        // Remove the invoker
                        // Reached the end, don't care to save
                        if ((it != m_invokers.end()) && (it == --m_invokers.end())) {
                            m_invokers.pop_back();
                            break;
                        }

                        // Swap with end and pop end.
                        auto last = m_invokers.back();
                        m_invokers.pop_back();

                        *it = last;
                        --it;
                    }
                }

                delete to_be_destroyed.front();
                to_be_destroyed.pop();
            }

            Punity::Screen.load_background();

            // No particular order
            // Notice that I don't do any particular checks.
            // That means inactive and destroyed objects are still called
            // However, that only happens if in this frame they were committed
            // Otherwise, the next frame will remove them.

            print_tree_of_entities();
            for (auto entity: m_all_entities) {
                // Update the components
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

            // Loop through all invokers and resolve them
            for (auto it = m_invokers.begin(); it != m_invokers.end(); ++it) {
                // If execution time has reached its point, lets invoke the function
                if ((*it)->get_execution_time() <= Punity::Time.time) {
                    (*it)->execute_function();
                    delete *it;

                    // Remove the invoker
                    // Reached the end, don't care to save
                    if ((it != m_invokers.end()) && (it == --m_invokers.end())) {
                        m_invokers.pop_back();
                        break;
                    }

                    // Swap with end and pop end.
                    auto last = m_invokers.back();
                    m_invokers.pop_back();

                    *it = last;
                    --it;
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
                        common_collider->add_collider(dynamic_collider);
                        dynamic_collider->get_entity()->report_start_collision_to_components(common_collider);
                        common_collider->get_entity()->report_start_collision_to_components(dynamic_collider);
                    }
                    else if (!has_collided && collider_in_list != nullptr) {
                        // If this hasn't collided BUT it exists, delete it and report the event
                        dynamic_collider->delete_collider(common_collider);
                        common_collider->delete_collider(dynamic_collider);
                        dynamic_collider->get_entity()->report_end_collision_to_components(common_collider);
                        common_collider->get_entity()->report_end_collision_to_components(dynamic_collider);
                    }
                }
            }

            // Now, draw the sprites!
            for (auto sprite : sprites) {
                Punity::Screen.draw_sprite(
                        sprite->get_entity()->get_transform()->global_position.x + sprite->offset.x,
                        sprite->get_entity()->get_transform()->global_position.y + sprite->offset.y,
                        sprite->height,
                        sprite->width,
                        sprite->get_sprite(),
                        sprite->get_alpha()
                        );
            }


            // Then draw the UI!
            for (auto sprite : ui_sprites) {
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

            sprites.clear();
            ui_sprites.clear();
            all_colliders.clear();
            dynamic_colliders.clear();

            if (time_difference < m_frame_delay_us) {
                sleep_us(m_frame_delay_us - time_difference);
            }
        }
    }
    void PEngine::register_entity(PEntity* entity) {
        for (auto _entity : m_all_entities) {
            if (_entity->get_id() == entity->get_id()) {
                // If the entity is already registered, don't register it twice
                return;
            }
        }

        std::cout << "Enabled " << entity->get_name() << '\n';
        entity->report_enable_to_components();
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

    void PEngine::register_invoker(Utils::PInvokableBase * invoker) {
        m_invokers.push_front(invoker);
    }

    // Returns first active entity with this name
    PEntity *PEngine::find_entity(std::string name) {
        for (auto entity : m_all_entities) {
            if (entity->get_name() == name)
                return entity;
        }
        return nullptr;
    }

    void PEngine::print_tree_of_entities() {
        std::cout << "----- ENTITIES -----\n";
        root_entity->print_tree(0);
        std::cout << "--------------------\n";
    }
}