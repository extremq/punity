//
// Created by god on 06.12.2022.
//

#include "punity/Entity/PEntity.h"
#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"

namespace Punity::Collision {
    float distance(Punity::Utils::PVector const& a, Punity::Utils::PVector const& b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

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

        // If is a trigger return before modifying position of circle
        if (rect->is_trigger || circle->is_trigger) return true;

        // Resolution
        circle_pos.x -= ray_to_nearest_point.x / mag * overlap;
        circle_pos.y -= ray_to_nearest_point.y / mag * overlap;

        circle->get_entity()->get_transform()->set_global(circle_pos);

        return true;
    }

    bool solve_circle_circle(Components::PCircleCollider* circle1, Components::PCircleCollider* circle2) {
        Utils::PVector circle1_pos = circle1->get_entity()->get_transform()->global_position;
        Utils::PVector circle2_pos = circle2->get_entity()->get_transform()->global_position;

        float dist = distance(circle1_pos, circle2_pos);

        // Not intersecting
        if (dist > circle1->radius + circle2->radius) return false;

        // No resolution should be made
        if (circle1->is_trigger || circle2->is_trigger) return true;

        // get the vector from the center of circle2 that points
        // to center of circle1
        // normalize it and multiply it by the sum of radii
        Utils::PVector tg;
        tg.x = (circle2_pos.x - circle1_pos.x) / dist;
        tg.y = (circle2_pos.y - circle1_pos.y) / dist;

        circle1_pos = circle2_pos - tg * (circle1->radius + circle2->radius);
        circle1->get_entity()->get_transform()->set_global(circle1_pos);

        return true;
    }
}