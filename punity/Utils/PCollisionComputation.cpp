//
// Created by god on 06.12.2022.
//

#include "punity/Entity/PEntity.h"
#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"

namespace Punity::Collision {
    bool solve_circle_rect(Components::PCircleCollider* circle, Components::PBoxCollider* rect) {
        Utils::PVector nearest_point;
        Utils::PVector rect_pos = rect->get_entity()->get_transform()->global_position;
        Utils::PVector circle_pos = circle->get_entity()->get_transform()->global_position;

        // Mathematics
        nearest_point.x = std::max(rect_pos.x - rect->width / 2, std::min(circle_pos.x, rect_pos.x + rect->width / 2));
        nearest_point.y = std::max(rect_pos.y - rect->height / 2, std::min(circle_pos.y, rect_pos.y + rect->height / 2));

        // Ray to nearest point
        Utils::PVector ray_to_nearest_point = nearest_point - circle_pos;

        const float mag = ray_to_nearest_point.mag();
        const float overlap = circle->radius - mag;

        if (overlap < -1e-5) return false;

        // If rect is a trigger return before modifying position of circle
        if (rect->is_trigger) return true;

        // Resolution
        circle_pos.x -= ray_to_nearest_point.x / mag * overlap;
        circle_pos.y -= ray_to_nearest_point.y / mag * overlap;

        circle->get_entity()->get_transform()->set_global(circle_pos);

        return true;
    }
}