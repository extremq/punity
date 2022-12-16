//
// Created by god on 07.12.2022.
//

#include "GameplayPrefabCreator.h"

#include "game/Assets/sprites.h"
#include "game/Assets/sprite_layers.h"
#include "game/Assets/colliders.h"

#include "punity/Components/PCircleCollider.h"
#include "punity/Components/PBoxCollider.h"

#include "PlayerBehaviour.h"
#include "RoomBehaviour.h"
#include "ActorBehaviour.h"
#include "Projectile.h"
#include "EnemyBehaviour.h"
#include "Weapon.h"
#include "EnergyPickup.h"

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

        // Add components
        player_entity->add_component<PlayerBehaviour>();
        player_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::player_h / 2.0f)
                ->set_static(false)
                ->set_information(Game::Colliders::COLLIDER_PLAYER);
        player_entity->add_component<ActorBehaviour>();
        player_entity->add_component<Weapon>()->set_weapon(Weapons::starting_weapon);

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
                ->set_information(Game::Colliders::COLLIDER_ENEMY);

        // Set enemy behaviour
        enemy_entity->add_component<EnemyBehaviour>();

        // Set actor behaviour
        enemy_entity->add_component<ActorBehaviour>();

        // TODO use level and scene to change these
        enemy_entity->add_component<Weapon>()->set_weapon(Weapons::enemy_weapon);

        // Entity for selector that appears above enemy when player aims at
        auto selector_entity = Punity::PEntity::make_entity("Selector", enemy_entity, false);

        selector_entity->get_transform()->set_local({0, -8});
        selector_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::enemy_selected_arrow,
                Game::Sprites::enemy_selected_arrow_alpha,
                Game::Sprites::enemy_selected_arrow_h,
                Game::Sprites::enemy_selected_arrow_w,
                Game::Sprites::Layers::SELECTOR
        );

        return enemy_entity;
    }


    Punity::PEntity* make_player_bullet(Punity::PEntity* parent, uint8_t projectile_type) {
        auto bullet_entity = Punity::PEntity::make_entity("PBullet", parent, true);

        // Set sprite according to projectile type
        auto collider = bullet_entity->add_component<Punity::Components::PCircleCollider>();

        switch (projectile_type) {
            // For each projectile, set the sprite and set the according size for the circle collider
            case Colliders::COLLIDER_PLAYER_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::player_bullet_1,
                        Game::Sprites::player_bullet_1_alpha,
                        Game::Sprites::player_bullet_1_h,
                        Game::Sprites::player_bullet_1_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::player_bullet_1_w / 2.0f);
                break;
            case Colliders::COLLIDER_PLAYER_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::player_bullet_2,
                        Game::Sprites::player_bullet_2_alpha,
                        Game::Sprites::player_bullet_2_h,
                        Game::Sprites::player_bullet_2_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::player_bullet_2_w / 2.0f);
                break;
            case Colliders::COLLIDER_PLAYER_PROJECTILE_3:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::player_bullet_3,
                        Game::Sprites::player_bullet_3_alpha,
                        Game::Sprites::player_bullet_3_h,
                        Game::Sprites::player_bullet_3_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::player_bullet_3_w / 2.0f);
                break;
            default:
                break;
        }

        // Set the rest of the collider info
        collider->set_information(projectile_type)
                ->set_trigger(true)
                ->set_static(false);

        // And add the projectile
        bullet_entity->add_component<Projectile>()
                ->set_exception(Game::Colliders::COLLIDER_PLAYER);

        return bullet_entity;
    }

    Punity::PEntity* make_enemy_bullet(Punity::PEntity* parent, uint8_t projectile_type) {
        auto bullet_entity = Punity::PEntity::make_entity("EBullet", parent, true);

        // Set sprite according to projectile type
        auto collider = bullet_entity->add_component<Punity::Components::PCircleCollider>();

        switch (projectile_type) {
            // For each projectile, set the sprite and set the according size for the circle collider
            case Colliders::COLLIDER_ENEMY_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::enemy_bullet_1,
                        Game::Sprites::enemy_bullet_1_alpha,
                        Game::Sprites::enemy_bullet_1_h,
                        Game::Sprites::enemy_bullet_1_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::enemy_bullet_1_w / 2.0f);
                break;
            case Colliders::COLLIDER_ENEMY_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::enemy_bullet_2,
                        Game::Sprites::enemy_bullet_2_alpha,
                        Game::Sprites::enemy_bullet_2_h,
                        Game::Sprites::enemy_bullet_2_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::enemy_bullet_2_w / 2.0f);
                break;
            case Colliders::COLLIDER_ENEMY_PROJECTILE_3:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::enemy_bullet_3,
                        Game::Sprites::enemy_bullet_3_alpha,
                        Game::Sprites::enemy_bullet_3_h,
                        Game::Sprites::enemy_bullet_3_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::enemy_bullet_3_w / 2.0f);
                break;
            default:
                break;
        }

        // Set the rest of the collider info
        collider->set_information(projectile_type)
                ->set_trigger(true)
                ->set_static(false);

        // And add the projectile
        bullet_entity->add_component<Projectile>()
                ->set_exception(Game::Colliders::COLLIDER_ENEMY);

        return bullet_entity;
    }

    Punity::PEntity* make_gameplay_UI(Punity::PEntity* parent) {
        auto gameplay_UI_entity = Punity::PEntity::make_entity("GameplayUI", parent, true);

        // Hearts system
        auto hearts_entity = Punity::PEntity::make_entity("Hearts", gameplay_UI_entity, true);
        auto heart1 = Punity::PEntity::make_entity("Heart1", hearts_entity, true);
        auto heart2 = Punity::PEntity::make_entity("Heart2", hearts_entity, true);
        auto heart3 = Punity::PEntity::make_entity("Heart3", hearts_entity, true);

        // Place and set hearts
        heart1->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::heart,
                Game::Sprites::heart_alpha,
                Game::Sprites::heart_h,
                Game::Sprites::heart_w,
                Game::Sprites::Layers::HUD
                );

        // Beware esoteric computations
        heart1->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                - 56.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        };

        heart2->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::heart,
                Game::Sprites::heart_alpha,
                Game::Sprites::heart_h,
                Game::Sprites::heart_w,
                Game::Sprites::Layers::HUD
        );

        heart2->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                - 48.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        };

        heart3->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::heart,
                Game::Sprites::heart_alpha,
                Game::Sprites::heart_h,
                Game::Sprites::heart_w,
                Game::Sprites::Layers::HUD
        );

        heart3->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                - 40.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        };

        // Energy counting system
        auto energy_hud_entity = Punity::PEntity::make_entity("EnergyHUD", gameplay_UI_entity, true);
        auto energy_image = Punity::PEntity::make_entity("EnergyImg", energy_hud_entity, true);

        energy_image->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::energy,
                Game::Sprites::energy_alpha,
                Game::Sprites::energy_h,
                Game::Sprites::energy_w,
                Game::Sprites::Layers::HUD
        );

        energy_image->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                54.0f - Game::Sprites::energy_w * 0.5f,
                - 64.0f + Game::Sprites::energy_h * 0.5f
        };

        auto energy_digit_1 = Punity::PEntity::make_entity("EnergyD1", energy_hud_entity, true);
        auto energy_digit_2 = Punity::PEntity::make_entity("EnergyD2", energy_hud_entity, true);

        energy_digit_1->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::nine,
                Game::Sprites::nine_alpha,
                Game::Sprites::nine_h,
                Game::Sprites::nine_w,
                Game::Sprites::Layers::HUD
        );

        energy_digit_1->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                40.0f - Game::Sprites::nine_w * 0.5f,
                - 65.0f + Game::Sprites::nine_h * 0.5f
        };

        energy_digit_2->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::nine,
                Game::Sprites::nine_alpha,
                Game::Sprites::nine_h,
                Game::Sprites::nine_w,
                Game::Sprites::Layers::HUD
        );

        energy_digit_2->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                48.0f - Game::Sprites::nine_w * 0.5f,
                - 65.0f + Game::Sprites::nine_h * 0.5f
        };

        // Level - stage hud
        auto counter_entity = Punity::PEntity::make_entity("Counter", gameplay_UI_entity, true);
        auto level_counter_entity = Punity::PEntity::make_entity("LevelCounter", counter_entity, true);
        auto dash_entity = Punity::PEntity::make_entity("DashChar", counter_entity, true);
        auto stage_counter_entity = Punity::PEntity::make_entity("StageCounter", counter_entity, true);

        level_counter_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::one,
                Game::Sprites::one_alpha,
                Game::Sprites::one_h,
                Game::Sprites::one_w,
                Game::Sprites::Layers::HUD
        );

        level_counter_entity->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                - 11.0f + Game::Sprites::one_w * 0.5f,
                - 65.0f + Game::Sprites::one_h * 0.5f
        };

        dash_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::dash,
                Game::Sprites::dash_alpha,
                Game::Sprites::dash_h,
                Game::Sprites::dash_w,
                Game::Sprites::Layers::HUD
        );

        dash_entity->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                0,
                - 63.0f + Game::Sprites::dash_h * 0.5f
        };

        stage_counter_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::one,
                Game::Sprites::one_alpha,
                Game::Sprites::one_h,
                Game::Sprites::one_w,
                Game::Sprites::Layers::HUD
        );

        stage_counter_entity->get_component<Punity::Components::PUISpriteRenderer>()->ui_position = {
                12.0f - Game::Sprites::one_w * 0.5f,
                - 65.0f + Game::Sprites::one_h * 0.5f
        };


        return gameplay_UI_entity;
    }

    Punity::PEntity* make_energy_pickup(Punity::PEntity* parent) {
        auto energy_pickup_entity = Punity::PEntity::make_entity("EnergyPickup", parent, true);

        energy_pickup_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::energy,
                Game::Sprites::energy_alpha,
                Game::Sprites::energy_h,
                Game::Sprites::energy_w,
                Game::Sprites::Layers::ENERGY_PICKUP
                );

        // A static trigger type.
        energy_pickup_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::energy_w / 2.0f)
                ->set_information(Colliders::COLLIDER_ENERGY_PICKUP)
                ->set_trigger(true)
                ->set_static(true);

        energy_pickup_entity->add_component<EnergyPickup>();

        return energy_pickup_entity;
    }

} // GameplayPrefabCreator