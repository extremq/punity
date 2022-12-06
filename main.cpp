//
// Created by god on 11.11.2022.
//
#include "punity/Punity.h"
#include "game/Logic/SceneManager.h"

int main() {
    // 2 seconds for our OS to catch the buffer
    stdio_init_all();
    sleep_ms(2000);

    Game::SceneManager::start_manager();
}