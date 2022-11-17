//
// Created by god on 12.11.2022.
//

#include "PSpriteRenderer.h"
#include "punity/Entity/PEntity.h"

namespace Punity {
    void Components::PSpriteRenderer::on_kill_myself() {
        entity->add_component<PSpriteRenderer>();
    }

    void Components::PSpriteRenderer::on_update() {
        std::cout << entity << '\n';
        entity->get_component<PSpriteRenderer>()->on_kill_myself();
    }
} // Punity