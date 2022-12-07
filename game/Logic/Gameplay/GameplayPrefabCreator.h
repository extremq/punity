//
// Created by god on 07.12.2022.
//

#ifndef _GAMEPLAYPREFABCREATOR_H
#define _GAMEPLAYPREFABCREATOR_H

#include "punity/Punity.h"

namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player();
    Punity::PEntity* make_enemies();
    Punity::PEntity* make_room();
} // GameplayPrefabCreator

#endif //_GAMEPLAYPREFABCREATOR_H
