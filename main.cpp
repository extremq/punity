//
// Created by god on 11.11.2022.
//
#include "punity/Punity.h"
#include "game/Logic/GameStateManager.h"

int main() {
    // 2 seconds for our OS to catch the buffer
    stdio_init_all();
    sleep_ms(2000);

    auto game_manager = Punity::PEntity::make_entity("game_manager");
    game_manager->add_component<Game::GameStateManager>();

    Punity::Engine.set_framerate(60);
    Punity::Engine.start_game();
}