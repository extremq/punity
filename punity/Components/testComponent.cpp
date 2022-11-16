//
// Created by god on 15.11.2022.
//

#include <iostream>
#include <hardware/timer.h>
#include "testComponent.h"
#include "punity/Entity/PEntity.h"

void Punity::Components::testComponent::on_update() {
    if (time_us_64() > 10 * 1000 * 1000) {
        entity->get_children().front()->set_active(true);
    }
    else if (time_us_64() > 5 * 1000 * 1000) {
        entity->get_children().front()->set_active(false);
    }
}