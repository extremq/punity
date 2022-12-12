//
// Created by god on 08.12.2022.
//

#include "PlayerBehaviour.h"
#include "punity/Components/PCollider.h"
#include "ActorBehaviour.h"

namespace Game {

    bool PlayerBehaviour::has_touched_chest() {
        return m_has_touched_chest;
    }

    void PlayerBehaviour::on_start_collision(Punity::Components::PCollider *other) {
        // Testing only
        if (other->get_entity()->get_name() == "Chest") {
            m_has_touched_chest = true;
        }
        else if (other->get_entity()->get_name() == "Enemy") {
            other->get_entity()->get_component<ActorBehaviour>()->subtract_hitpoints(6);
            other->get_entity()->set_active(false);
        }
    }

    void PlayerBehaviour::on_enable() {
        std::cout << "Player enabled\n";
        reset_status();
    }

    void PlayerBehaviour::reset_status() {
        m_has_touched_chest = false;
        get_entity()->get_transform()->set_global({0, 0});
    }

    void PlayerBehaviour::on_update() {
        compute_movement();
    }

    void PlayerBehaviour::compute_movement() {
        // Construct vector of direction
        auto joystick_direction = Punity::Utils::PVector();
        joystick_direction.x = Punity::Joystick.get_x_direction();
        joystick_direction.y = Punity::Joystick.get_y_direction();

        // Normalize the vector
        joystick_direction = joystick_direction.norm();

        // Translate the player
        get_entity()->get_transform()->translate(joystick_direction * Punity::Time.delta_time * 30);
    }
} // Game