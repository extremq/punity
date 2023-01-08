//
// Created by xnydd on 1/8/2023.
//

#include "MovingBehaviour.h"
#include "punity/Utils/PMath.h"

namespace Game {
    void MovingBehaviour::translate_to(Punity::Utils::PVector target, float time) {
        if (time < 0.001f) {
            // If it's instant, let's just teleport
            get_entity()->get_transform()->set_global(target);
            return;
        }

        // Mark this as translating
        is_translating = true;
        target_position = target;

        Punity::Utils::PVector current_position = get_entity()->get_transform()->global_position;

        // If the positions are pretty much the same, don't translate
        float dist = Punity::Utils::distance(current_position, target_position);

        if (dist < 0.005f) {
            is_translating = false;
            return;
        }

        end_time = Punity::Time.time + time;

        translation_increment = (target_position - current_position) / time;
    }

    void MovingBehaviour::on_update() {
        if (!is_translating) return;

        get_entity()->get_transform()->translate(translation_increment * Punity::Time.delta_time);

        if (end_time < Punity::Time.time) {
            is_translating = false;
        }
    }
} // Game