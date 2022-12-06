//
// Created by god on 05.12.2022.
//

#include "Room.h"
#include "punity/Utils/PInvokable.h"
#include "game/sprites.h"

namespace Game {
    void Room::on_update() {
        PComponent::on_update();
    }

    // When this is enabled, setup the level!
    // Only enabled/disabled when entering from
    // Loading screens
    void Room::on_enable() {
        setup_level();
    }

    void Room::on_disable() {
        disintegrate_stage();
    }

    void Room::generate_stage() {
        // Build the room in a BEAUTIFUL way.
        for (counter_x = 0; counter_x < 16; ++counter_x) {
            for (counter_y = 0; counter_y < 16; ++counter_y) {
                if (counter_y == 0 || counter_y == 15 || counter_x == 0 || counter_x == 15)
                    tiles[counter_x][counter_y] = WALL;
                solve_tile();

            }
        }
    }

    // A bit complicated looking because my invoker is not
    // the most advanced on earth.
    void Room::solve_tile() {
        switch(tiles[counter_x][counter_y]) {
            case EMPTY:
                break;
            case WALL:
                new Punity::Utils::PInvokableWithInt<Room>(
                        &Room::make_wall,
                        counter_x + counter_y * 16,
                        this,
                        counter_x * 0.025 + counter_y * 0.025,
                        entity->get_id()
                );
                break;
        }
    }

    void Room::disintegrate_stage() {
        entity->destroy_children();
    }

    void Room::setup_level() {
        generate_stage();
    }

    void Room::make_wall(int index) {
        auto tile = Punity::PEntity::make_entity("tile");
        auto sprite = tile->add_component<Punity::Components::PSpriteRenderer>();
        Punity::Utils::PVector pos(index % 16 * 8 - 60,
                                   index / 16 * 8 - 60);
        tile->get_transform()->set_global(pos);

        sprite->set_sprite(
                Game::Sprites::placeholder_wall,
                Game::Sprites::placeholder_wall_alpha,
                Game::Sprites::placeholder_wall_h,
                Game::Sprites::placeholder_wall_w,
                WALL_LAYER
        );

        tile->set_parent(entity);
    }

} // Game