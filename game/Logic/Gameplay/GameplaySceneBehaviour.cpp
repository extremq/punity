//
// Created by god on 05.12.2022.
//

#include "GameplaySceneBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "game/Assets/sprites.h"

namespace Game {
    void GameplaySceneBehaviour::on_update() {
        PComponent::on_update();
    }

    // When this is enabled, setup the level!
    // Only enabled/disabled when entering from
    // Loading screens
    void GameplaySceneBehaviour::on_enable() {
        setup_stage();
    }

    void GameplaySceneBehaviour::setup_stage() {
        // Make room and actors entities to group the tiles and the enemies
        if (room == nullptr) {
            room = Punity::PEntity::make_entity("Room");
            room->set_parent(this->get_entity());
        }

        if (enemies == nullptr) {
            enemies = Punity::PEntity::make_entity("Enemies");
            enemies->set_parent(this->get_entity());
        }

        // Show the enemies at a later point
        enemies->set_active(false);

        if (player == nullptr) {
            player = Punity::PEntity::make_entity("Player");
            enemies->set_parent(this->get_entity());
        }

        // Show the player at a later point
        player->set_active(false);

        // Start generating the map right away
        generate_stage();

        // Show the player with a delay of 1 second
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::show_player,
                this,
                PLAYER_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );

        // Make the enemies with a delay of 2 seconds
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::make_enemies,
                this,
                ENEMY_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );
    }

    void GameplaySceneBehaviour::cleanup_stage() {
        disintegrate_stage();
    }

    void GameplaySceneBehaviour::generate_stage() {
        // Border the room
        for (row_counter = 0; row_counter < 16; ++row_counter) {
            for (column_counter = 0; column_counter < 16; ++column_counter) {
                if (column_counter == 0 || column_counter == 15 || row_counter == 0 || row_counter == 15)
                    tiles[row_counter][column_counter] = WALL;
                else
                    tiles[row_counter][column_counter] = EMPTY;
            }
        }

        // Make each tile
        for (int row = 0; row < 16; ++row) {
            for (int column = 0; column < 16; ++column) {
                solve_tile(row, column, (row + column) * 0.03, tiles[row][column]);
            }
        }
    }

    // A bit complicated looking because my invoker is not
    // the most advanced on earth.
    void GameplaySceneBehaviour::solve_tile(uint8_t row, uint8_t column, float delay, Tile tile) {
        switch(tile) {
            case EMPTY:
                break;
            case WALL:
                // Invoke the make_wall function with the specified delay
                new Punity::Utils::PInvokableWithInt<GameplaySceneBehaviour>(
                        &GameplaySceneBehaviour::make_wall,
                        row + column * 16,
                        this,
                        delay,
                        get_entity()->get_id()
                );
                break;
        }
    }

    void GameplaySceneBehaviour::disintegrate_stage() {
        get_entity()->destroy_children();
    }

    void GameplaySceneBehaviour::make_wall(int index) {
        auto tile = Punity::PEntity::make_entity("tile");
        auto sprite = tile->add_component<Punity::Components::PSpriteRenderer>();

        // Compute the position based on tile index
        Punity::Utils::PVector pos(index % 16 * 8 - 60,
                                   index / 16 * 8 - 60);

        // Set the position
        tile->get_transform()->set_global(pos);

        // Choose sprite
        sprite->set_sprite(
                Game::Sprites::placeholder_wall,
                Game::Sprites::placeholder_wall_alpha,
                Game::Sprites::placeholder_wall_h,
                Game::Sprites::placeholder_wall_w,
                WALL_LAYER
        );

        // Attach it to the room
        tile->set_parent(room);
    }

    void GameplaySceneBehaviour::show_player() {
        player->set_active(true);
    }

    void GameplaySceneBehaviour::show_chest() {

    }

    void GameplaySceneBehaviour::make_enemies() {

    }
} // Game