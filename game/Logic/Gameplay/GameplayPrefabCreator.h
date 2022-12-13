//
// Created by god on 07.12.2022.
//

#ifndef _GAMEPLAYPREFABCREATOR_H
#define _GAMEPLAYPREFABCREATOR_H

#include "punity/Punity.h"

namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player(Punity::PEntity* parent);
    Punity::PEntity* make_enemies_entity(Punity::PEntity* parent);
    Punity::PEntity* make_enemy(Punity::PEntity* parent);
    Punity::PEntity* make_room(Punity::PEntity* parent);
    Punity::PEntity* make_chest(Punity::PEntity* parent);
    Punity::PEntity* make_wall(Punity::PEntity* parent);
    Punity::PEntity* make_player_bullet(Punity::PEntity* parent);
    Punity::PEntity* make_enemy_bullet(Punity::PEntity* parent);
    Punity::PEntity* make_gameplay_UI(Punity::PEntity* parent);
} // GameplayPrefabCreator

#endif //_GAMEPLAYPREFABCREATOR_H
