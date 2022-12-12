//
// Created by god on 12.12.2022.
//

#ifndef _GAMEPLAYSCENEMANAGER_H
#define _GAMEPLAYSCENEMANAGER_H

// Used by any entity to have a nice and fast way of knowing the state of gameplay

namespace Game::GameplaySceneManager {
    extern bool player_loaded;
    extern bool enemies_loaded;
    extern bool chest_loaded;
} // Game

#endif //_GAMEPLAYSCENEMANAGER_H
