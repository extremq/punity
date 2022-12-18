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
#include "AttractablePickup.h"
#include "ChestBehaviour.h"
#include "WeaponPickup.h"

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
                ->set_information(Game::Colliders::PLAYER);
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

        // Add its behavour
        chest_entity->add_component<ChestBehaviour>();


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
                ->set_information(Game::Colliders::ENEMY);

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
            case Colliders::PLAYER_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::player_bullet_1,
                        Game::Sprites::player_bullet_1_alpha,
                        Game::Sprites::player_bullet_1_h,
                        Game::Sprites::player_bullet_1_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::player_bullet_1_w / 2.0f);
                break;
            case Colliders::PLAYER_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::player_bullet_2,
                        Game::Sprites::player_bullet_2_alpha,
                        Game::Sprites::player_bullet_2_h,
                        Game::Sprites::player_bullet_2_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::player_bullet_2_w / 2.0f);
                break;
            case Colliders::PLAYER_PROJECTILE_3:
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
                ->set_exception(Game::Colliders::PLAYER);

        return bullet_entity;
    }

    Punity::PEntity* make_enemy_bullet(Punity::PEntity* parent, uint8_t projectile_type) {
        auto bullet_entity = Punity::PEntity::make_entity("EBullet", parent, true);

        // Set sprite according to projectile type
        auto collider = bullet_entity->add_component<Punity::Components::PCircleCollider>();

        switch (projectile_type) {
            // For each projectile, set the sprite and set the according size for the circle collider
            case Colliders::ENEMY_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::enemy_bullet_1,
                        Game::Sprites::enemy_bullet_1_alpha,
                        Game::Sprites::enemy_bullet_1_h,
                        Game::Sprites::enemy_bullet_1_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::enemy_bullet_1_w / 2.0f);
                break;
            case Colliders::ENEMY_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        Game::Sprites::enemy_bullet_2,
                        Game::Sprites::enemy_bullet_2_alpha,
                        Game::Sprites::enemy_bullet_2_h,
                        Game::Sprites::enemy_bullet_2_w,
                        Game::Sprites::Layers::BULLET
                );
                collider->set_radius(Game::Sprites::enemy_bullet_2_w / 2.0f);
                break;
            case Colliders::ENEMY_PROJECTILE_3:
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
                ->set_exception(Game::Colliders::ENEMY);

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


        // Selected weapon hud
        auto weapon_status_entity = Punity::PEntity::make_entity("WeaponStatusUI", gameplay_UI_entity, true);
        auto arrow_entity = Punity::PEntity::make_entity("WeaponArrow", weapon_status_entity, true);
        arrow_entity->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                 0,
                 63.0f - Game::Sprites::arrow_left_h / 2.0f
                })
                ->set_sprite(
                Game::Sprites::arrow_left,
                Game::Sprites::arrow_left_alpha,
                Game::Sprites::arrow_left_h,
                Game::Sprites::arrow_left_w,
                Game::Sprites::Layers::HUD
                );

        // Make Default weapon energy, energy counter, damage, damage counter
        auto default_weapon_entity = Punity::PEntity::make_entity("DefaultWeapon", weapon_status_entity, true);
        auto default_weapon_energy = Punity::PEntity::make_entity("DefWpnEnergy", default_weapon_entity, true);
        auto default_weapon_energy_counter = Punity::PEntity::make_entity("DefWpnEnergyCnt", default_weapon_entity, true);
        auto default_weapon_attack = Punity::PEntity::make_entity("DefWpnAttack", default_weapon_entity, true);
        auto default_weapon_attack_counter = Punity::PEntity::make_entity("DefWpnAttackCnt", default_weapon_entity, true);

        default_weapon_energy_counter->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                     -65.0f + 16.0f + Game::Sprites::zero_w / 2.0f,
                     63.0f - Game::Sprites::zero_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::zero,
                        Game::Sprites::zero_alpha,
                        Game::Sprites::zero_h,
                        Game::Sprites::zero_w,
                        Game::Sprites::Layers::HUD
                );

        default_weapon_energy->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         -64.0f + 24.0f + Game::Sprites::energy_w / 2.0f,
                         62.0f - Game::Sprites::energy_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::energy,
                        Game::Sprites::energy_alpha,
                        Game::Sprites::energy_h,
                        Game::Sprites::energy_w,
                        Game::Sprites::Layers::HUD
                );


        default_weapon_attack_counter->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         -65.0f + 36.0f + Game::Sprites::one_w / 2.0f,
                         63.0f - Game::Sprites::one_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::one,
                        Game::Sprites::one_alpha,
                        Game::Sprites::one_h,
                        Game::Sprites::one_w,
                        Game::Sprites::Layers::HUD
                );

        default_weapon_attack->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         -64.0f + 44.0f + Game::Sprites::sword_w / 2.0f,
                         63.0f - Game::Sprites::sword_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::sword,
                        Game::Sprites::sword_alpha,
                        Game::Sprites::sword_h,
                        Game::Sprites::sword_w,
                        Game::Sprites::Layers::HUD
                );


        // Make Equipped weapon energy, energy counter, damage, damage counter but have it inactive
        auto equipped_weapon_entity = Punity::PEntity::make_entity("EquippedWeapon", weapon_status_entity, false);
        auto equipped_weapon_energy = Punity::PEntity::make_entity("EqpWpnEnergy", equipped_weapon_entity, true);
        auto equipped_weapon_energy_counter = Punity::PEntity::make_entity("EqpWpnEnergyCnt", equipped_weapon_entity, true);
        auto equipped_weapon_attack = Punity::PEntity::make_entity("EqpWpnAttack", equipped_weapon_entity, true);
        auto equipped_weapon_attack_counter = Punity::PEntity::make_entity("EqpWpnAttackCnt", equipped_weapon_entity, true);

        equipped_weapon_energy_counter->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         12.0f + Game::Sprites::zero_w / 2.0f,
                         63.0f - Game::Sprites::zero_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::zero,
                        Game::Sprites::zero_alpha,
                        Game::Sprites::zero_h,
                        Game::Sprites::zero_w,
                        Game::Sprites::Layers::HUD
                );

        equipped_weapon_energy->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         20.0f + Game::Sprites::energy_w / 2.0f,
                         62.0f - Game::Sprites::energy_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::energy,
                        Game::Sprites::energy_alpha,
                        Game::Sprites::energy_h,
                        Game::Sprites::energy_w,
                        Game::Sprites::Layers::HUD
                );


        equipped_weapon_attack_counter->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         30.0f + Game::Sprites::one_w / 2.0f,
                         63.0f - Game::Sprites::one_h / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::one,
                        Game::Sprites::one_alpha,
                        Game::Sprites::one_h,
                        Game::Sprites::one_w,
                        Game::Sprites::Layers::HUD
                );

        equipped_weapon_attack->add_component<Punity::Components::PUISpriteRenderer>()
                ->set_ui_pos({
                         38.0f + Game::Sprites::sword_h / 2.0f,
                         63.0f - Game::Sprites::sword_w / 2.0f
                })
                ->set_sprite(
                        Game::Sprites::sword,
                        Game::Sprites::sword_alpha,
                        Game::Sprites::sword_h,
                        Game::Sprites::sword_w,
                        Game::Sprites::Layers::HUD
                );

        return gameplay_UI_entity;
    }

    Punity::PEntity* make_energy_pickup(Punity::PEntity* parent) {
        auto energy_pickup_entity = Punity::PEntity::make_entity("EnergyPickup", parent, true);

        energy_pickup_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::energy,
                Game::Sprites::energy_alpha,
                Game::Sprites::energy_h,
                Game::Sprites::energy_w,
                Game::Sprites::Layers::PICKUP
                );

        // A static trigger type.
        energy_pickup_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::energy_w / 2.0f)
                ->set_information(Colliders::ENERGY_PICKUP)
                ->set_trigger(true)
                ->set_static(true);

        energy_pickup_entity->add_component<AttractablePickup>();

        return energy_pickup_entity;
    }

    Punity::PEntity* make_heart_pickup(Punity::PEntity* parent) {
        auto heart_pickup_entity = Punity::PEntity::make_entity("HeartPickup", parent, true);

        heart_pickup_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::heart,
                Game::Sprites::heart_alpha,
                Game::Sprites::heart_h,
                Game::Sprites::heart_w,
                Game::Sprites::Layers::PICKUP
        );

        // A static trigger type.
        heart_pickup_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::heart_w / 2.0f)
                ->set_information(Colliders::HEART_PICKUP)
                ->set_trigger(true)
                ->set_static(true);

        heart_pickup_entity->add_component<AttractablePickup>();

        return heart_pickup_entity;
    }

    Punity::PEntity* make_weapon_pickup(Punity::PEntity* parent, Weapons::WeaponConfig config) {
        auto weapon_entity = Punity::PEntity::make_entity("WeaponPickup", parent, true);

        weapon_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Sprites::sword,
                Game::Sprites::sword_alpha,
                Game::Sprites::sword_h,
                Game::Sprites::sword_w,
                Game::Sprites::Layers::PICKUP
                );

        // Add and set the config of the weapon pickup
        weapon_entity->add_component<WeaponPickup>()->set_weapon(config);

        weapon_entity->add_component<Punity::Components::PBoxCollider>()
                ->set_size(Game::Sprites::sword_h, Game::Sprites::sword_w)
                ->set_trigger(true)
                ->set_information(Colliders::WEAPON_PICKUP);

        return weapon_entity;
    }


    // Spawns amount of energy pickups at a random offset of position
    void drop_energy_pickups(Punity::PEntity* parent, uint8_t amount, Punity::Utils::PVector position) {
        while (amount-- > 0) {
            // Create an energy pickup on death and set it at the same position + random offset
            Punity::Utils::PVector random_spawn_position(Punity::Utils::random(-5.0f, 5.0f),
                                                         Punity::Utils::random(-5.0f, 5.0f));
            random_spawn_position += position;

            GameplayPrefabCreator::make_energy_pickup(parent)->get_transform()->set_global(
                    random_spawn_position
            );
        }
    }

    // Spawns amount of heart pickups at a random offset of position
    void drop_heart_pickups(Punity::PEntity* parent, uint8_t amount, Punity::Utils::PVector position) {
        while (amount-- > 0) {
            // Create an energy pickup on death and set it at the same position + random offset
            Punity::Utils::PVector random_spawn_position(Punity::Utils::random(-5.0f, 5.0f),
                                                         Punity::Utils::random(-5.0f, 5.0f));
            random_spawn_position += position;

            GameplayPrefabCreator::make_heart_pickup(parent)->get_transform()->set_global(
                    random_spawn_position
            );
        }
    }
} // GameplayPrefabCreator