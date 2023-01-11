//
// Created by god on 07.12.2022.
//

#ifndef _GAMEPLAYPREFABCREATOR_H
#define _GAMEPLAYPREFABCREATOR_H

#include "punity/Punity.h"
#include "punity/Utils/PVector.h"
#include "game/Assets/weapons.h"

namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player(Punity::PEntity* parent);
    Punity::PEntity* make_enemies_entity(Punity::PEntity* parent);
    Punity::PEntity* make_star(Punity::PEntity* parent);
    Punity::PEntity* make_enemy(Punity::PEntity* parent, uint8_t type);
    Punity::PEntity* make_room(Punity::PEntity* parent);
    Punity::PEntity* make_chest(Punity::PEntity* parent);
    Punity::PEntity* make_crate(Punity::PEntity* parent);
    Punity::PEntity* make_wall(Punity::PEntity* parent, uint16_t type);
    Punity::PEntity* make_player_bullet(Punity::PEntity* parent, uint8_t projectile_type);
    Punity::PEntity* make_enemy_bullet(Punity::PEntity* parent, uint8_t projectile_type);
    Punity::PEntity* make_gameplay_UI(Punity::PEntity* parent);
    Punity::PEntity* make_energy_pickup(Punity::PEntity* parent);
    Punity::PEntity* make_heart_pickup(Punity::PEntity* parent);
    Punity::PEntity* make_weapon_pickup(Punity::PEntity* parent, Weapons::WeaponConfig config, bool is_rare);

    void drop_energy_pickups(Punity::PEntity* parent, uint8_t amount, Punity::Utils::PVector position);
    void drop_heart_pickups(Punity::PEntity* parent, uint8_t amount, Punity::Utils::PVector position);
} // GameplayPrefabCreator

#endif //_GAMEPLAYPREFABCREATOR_H
