//
// Created by god on 18.11.2022.
//

#ifndef _PMOVEMENT_H
#define _PMOVEMENT_H

#include "punity/Punity.h"
#include "PSpriteRenderer.h"
#include "PCollider.h"
#include "PBoxCollider.h"
#include "game/Assets/sprites.h"
#include "punity/Utils/PInvokable.h"

namespace Punity::Components {
    class PMovement : public PComponent {
        bool active = false;
        float last = 0;

        void on_start() override {
            PEntity* i = nullptr;
            for (int z = 0; z < 100; ++z) {
                i = PEntity::make_entity("r" + std::to_string(z));
                i->add_component<Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::test_wall,
                        Game::Sprites::test_wall_alpha,
                        Game::Sprites::test_wall_h,
                        Game::Sprites::test_wall_w,
                        0);
                i->add_component<Components::PBoxCollider>()->width = 8;
                i->get_component<Components::PBoxCollider>()->height = 8;

                Utils::PVector rand(Utils::PRandom::get_random() * 100, Utils::PRandom::get_random() * 100);
                i->transform->set_global(rand);
            }
        }
        void on_update() override {
            Utils::PVector direction;
            direction.x = Punity::Joystick.get_x_direction();
            direction.y = Punity::Joystick.get_y_direction();
            direction = direction * 30.0f * Punity::Time.delta_time;
            entity->transform->translate(direction);
            Punity::Screen.camera = entity->transform->global_position;
        }

        void toggle_ui() {
            std::cout << "ayo\n";
            entity->get_component<PUISpriteRenderer>()->set_active(!entity->get_component<PUISpriteRenderer>()->is_globally_active());
        }

        void on_start_collision(PCollider* other) override {
            std::cout << "coll\n";
            new Utils::PInvokable<PMovement>(&PMovement::toggle_ui, this, 3, entity->get_id());
        }
    };

} // Components

#endif //_PMOVEMENT_H
