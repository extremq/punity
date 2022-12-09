//
// Created by god on 08.12.2022.
//

#include "RoomBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "punity/Components/PBoxCollider.h"
#include "GameplayPrefabCreator.h"

namespace Game {
    void RoomBehaviour::generate_stage() {
        // Border the room
        for (row_counter = 0; row_counter < 16; ++row_counter) {
            for (column_counter = 0; column_counter < 16; ++column_counter) {
                if (column_counter == 0)
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
    void RoomBehaviour::solve_tile(uint8_t row, uint8_t column, float delay, Tile tile) {
        switch(tile) {
            case EMPTY:
                break;
            case WALL:
                // Invoke the make_wall function with the specified delay
                new Punity::Utils::PInvokableWithInt<RoomBehaviour>(
                        &RoomBehaviour::make_wall,
                        row + column * 16,
                        this,
                        delay,
                        get_entity()->get_id()
                );
                break;
        }
    }

    void RoomBehaviour::make_wall(int index) {
        auto tile = GameplayPrefabCreator::make_wall(get_entity());

        // Compute the position based on tile index
        Punity::Utils::PVector pos(index % 16 * 8 - 60,
                                   index / 16 * 8 - 60);

        // Set the position
        tile->get_transform()->set_global(pos);
    }

    void RoomBehaviour::disintegrate_stage() {
        // Destroy the map, a new one will be generated next time
        get_entity()->destroy_children();
    }

    void RoomBehaviour::on_enable() {
        generate_stage();
    }

    void RoomBehaviour::on_disable() {
        disintegrate_stage();
    }
} // Game