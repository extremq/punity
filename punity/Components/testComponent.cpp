//
// Created by god on 15.11.2022.
//

#include <iostream>
#include <hardware/timer.h>
#include "testComponent.h"
#include "punity/Entity/PEntity.h"

void Punity::Components::testComponent::on_update() {
    if (time_us_64() > 15 * 1000 * 1000) {
        entity->destroy();
    }
    else if (time_us_64() > 10 * 1000 * 1000) {
        entity->get_children().front()->set_active(true);
    }
    else if (time_us_64() > 5 * 1000 * 1000) {
        entity->get_children().front()->set_active(false);
    }
}

void Punity::Components::testComponent::on_destroy() {
    // Try setting as parent a destroyed child
    // Should throw error
    (new PEntity("born"))->set_parent(entity->get_children().front());
}
