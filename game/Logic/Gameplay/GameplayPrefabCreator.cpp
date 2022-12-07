//
// Created by god on 07.12.2022.
//

#include "GameplayPrefabCreator.h"
#include "game/Assets/sprites.h"
#include "PlayerMovement.h"

namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player() {
        auto player_entity = Punity::PEntity::make_entity("Player");
        player_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::player,
                Game::Sprites::player_alpha,
                Game::Sprites::player_h,
                Game::Sprites::player_w,
                1
        );
        player_entity->add_component<PlayerMovement>();

        return player_entity;
    }

    Punity::PEntity* make_enemies() {
        return Punity::PEntity::make_entity("Enemies");
    }

    Punity::PEntity* make_room() {
        return Punity::PEntity::make_entity("Room");
    }
} // GameplayPrefabCreator