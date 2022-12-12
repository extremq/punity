//
// Created by god on 07.12.2022.
//

#include "GameplayPrefabCreator.h"
#include "game/Assets/sprites.h"
#include "punity/Components/PCircleCollider.h"
#include "PlayerBehaviour.h"
#include "RoomBehaviour.h"
#include "game/Assets/sprite_layers.h"
#include "punity/Components/PBoxCollider.h"


/*
 * Unity has things called "Prefabs". Basically, they are game objects (my Punity::PEntity)
 * that can have children, components and preset values. They are useful when you want to
 * create something a lot of times (such as tiles) and don't want to repeat yourself.
 * It's really useful to treat things as prefabs, both as an abstraction layer and as
 * a code clarity choice.
 */
namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player(Punity::PEntity* parent) {
        auto player_entity = Punity::PEntity::make_entity("Player", parent, false);
        player_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::player,
                Game::Sprites::player_alpha,
                Game::Sprites::player_h,
                Game::Sprites::player_w,
                Game::Sprites::Layers::PLAYER
        );

        // Add behaviour and Circle collider
        player_entity->add_component<PlayerBehaviour>();
        player_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::player_h / 2.0f)
                ->is_static = false;

        return player_entity;
    }

    Punity::PEntity* make_room(Punity::PEntity* parent) {
        auto room_entity = Punity::PEntity::make_entity("Room", parent, false);

        // Add the room_behaviour
        room_entity->add_component<RoomBehaviour>();

        return room_entity;
    }

    Punity::PEntity* make_chest(Punity::PEntity* parent) {
        auto chest_entity = Punity::PEntity::make_entity("Chest", parent, true);

        // Choose sprite
        chest_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::chest,
                Game::Sprites::chest_alpha,
                Game::Sprites::chest_h,
                Game::Sprites::chest_w,
                Game::Sprites::Layers::CHEST
        );

        // Use a box collider
        chest_entity->add_component<Punity::Components::PBoxCollider>()->set_size(
                Game::Sprites::chest_h,
                Game::Sprites::chest_w
        );

        chest_entity->get_transform()->set_global({0, 32});

        return chest_entity;
    }

    Punity::PEntity* make_wall(Punity::PEntity* parent) {
        auto wall_entity = Punity::PEntity::make_entity("Wall", parent, true);

        // Choose sprite
        wall_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::wall,
                Game::Sprites::wall_alpha,
                Game::Sprites::wall_h,
                Game::Sprites::wall_w,
                Game::Sprites::Layers::WALL
        );

        // Use a box collider
        wall_entity->add_component<Punity::Components::PBoxCollider>()->set_size(
                Game::Sprites::wall_h,
                Game::Sprites::wall_w
        );

        return wall_entity;
    }

    Punity::PEntity* make_enemies_entity(Punity::PEntity* parent) {
        auto enemies_entity = Punity::PEntity::make_entity("Enemies", parent, true);
        return enemies_entity;
    }

    Punity::PEntity* make_enemy(Punity::PEntity* parent) {
        auto enemy_entity = Punity::PEntity::make_entity("Enemy", parent, true);

        // Choose sprite
        enemy_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::first_enemy_type,
                Game::Sprites::first_enemy_type_alpha,
                Game::Sprites::first_enemy_type_h,
                Game::Sprites::first_enemy_type_w,
                Game::Sprites::Layers::PLAYER
                );

        // Set the collider
        enemy_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::first_enemy_type_h / 2)
                ->is_static = true;

        // TODO add enemy behaviour and actor behaviour

        return enemy_entity;
    }
} // GameplayPrefabCreator