//
// Created by god on 07.12.2022.
//

#include "GameplayPrefabCreator.h"

#include "game/Assets/sprites.h"
#include "game/Assets/sprite_layers.h"
#include "game/Assets/colliders.h"
#include "game/Assets/strings.h"
#include "game/Assets/groupings.h"

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
#include "CrateBehaviour.h"
#include "MovingBehaviour.h"

/*
 * Unity has things called "Prefabs". Basically, they are game objects (my Punity::PEntity)
 * that can have children, components and preset values. They are useful when you want to
 * create something a lot of times (such as tiles) and don't want to repeat yourself.
 * It's really useful to treat things as prefabs, both as an abstraction layer and as
 * a code clarity choice.
 */
namespace Game::GameplayPrefabCreator {
    Punity::PEntity* make_player(Punity::PEntity* parent) {
        auto player_entity = Punity::PEntity::make_entity(Game::Names::PLAYER, parent, false);
        player_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::player_normal, Game::Sprites::Layers::PLAYER)
        );

        // Add components
        player_entity->add_component<PlayerBehaviour>();
        player_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::player_normal_h / 2.0f)
                ->set_static(false)
                ->set_information(Game::Colliders::PLAYER);
        player_entity->add_component<ActorBehaviour>();
        player_entity->add_component<Weapon>()->set_weapon(Weapons::starting_weapon);

        // Add barrier for shielding from bullets
        auto barrier_entity = Punity::PEntity::make_entity(Game::Names::BARRIER, player_entity, false);
        barrier_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::barrier, Game::Sprites::Layers::PLAYER)
                );

        return player_entity;
    }

    Punity::PEntity* make_room(Punity::PEntity* parent) {
        auto room_entity = Punity::PEntity::make_entity(Game::Names::ROOM, parent, false);

        // Add the room_behaviour
        room_entity->add_component<RoomBehaviour>();

        return room_entity;
    }

    Punity::PEntity* make_chest(Punity::PEntity* parent) {
        auto chest_entity = Punity::PEntity::make_entity(Game::Names::CHEST, parent, true);

        // Choose sprite
        chest_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::chest, Game::Sprites::Layers::CHEST)
        );

        // Use a box collider
        chest_entity->add_component<Punity::Components::PBoxCollider>()->set_size(
                Game::Sprites::chest_h,
                Game::Sprites::chest_w
        );

        // Add its behavour
        chest_entity->add_component<ChestBehaviour>();


        return chest_entity;
    }

    Punity::PEntity* make_crate(Punity::PEntity* parent) {

        auto chest_entity = Punity::PEntity::make_entity(Game::Names::CHEST, parent, true);

        // Choose sprite
        chest_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::crate, Game::Sprites::Layers::WALL)
        );

        // Use a box collider
        chest_entity->add_component<Punity::Components::PBoxCollider>()->set_size(
                Game::Sprites::crate_h,
                Game::Sprites::crate_w
        );

        // Add its behavour
        chest_entity->add_component<CrateBehaviour>();

        return chest_entity;
    }

    Punity::PEntity* make_wall(Punity::PEntity* parent, uint16_t type) {
        auto wall_entity = Punity::PEntity::make_entity(Game::Names::WALL, parent, true);

        // Choose sprite
        wall_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Groupings::wall_types[type],
                Game::Sprites::wall_1_alpha,
                Game::Sprites::wall_1_h,
                Game::Sprites::wall_1_w,
                Game::Sprites::Layers::WALL
        );

        // Use a box collider
        wall_entity->add_component<Punity::Components::PBoxCollider>()->set_size(
                Game::Sprites::wall_1_h,
                Game::Sprites::wall_1_w
        );

        return wall_entity;
    }

    Punity::PEntity* make_enemies_entity(Punity::PEntity* parent) {
        auto enemies_entity = Punity::PEntity::make_entity(Game::Names::ENEMIES, parent, true);
        return enemies_entity;
    }

    Punity::PEntity* make_star(Punity::PEntity* parent) {
        auto star_entity = Punity::PEntity::make_entity(Game::Names::STAR, parent, false);
        star_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::star, Game::Sprites::Layers::HUD)
        );

        return star_entity;
    }

    Punity::PEntity* make_enemy(Punity::PEntity* parent, uint8_t type) {
        // Type goes from 0 -> 6
        auto enemy_entity = Punity::PEntity::make_entity(Game::Names::ENEMY, parent, true);

        // Choose sprite
        enemy_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                Game::Groupings::enemies[type],
                Game::Sprites::enemy_1_alpha,
                Game::Sprites::enemy_1_h,
                Game::Sprites::enemy_1_w,
                Game::Sprites::Layers::PLAYER
        );

        // Set the collider
        enemy_entity->add_component<Punity::Components::PCircleCollider>()
                ->set_radius(Game::Sprites::enemy_1_h / 2)
                ->set_information(Game::Colliders::ENEMY);

        // Set enemy behaviour
        enemy_entity->add_component<EnemyBehaviour>();

        // Set actor behaviour
        enemy_entity->add_component<ActorBehaviour>()->set_max_hitpoints(3 + type / 3);

        enemy_entity->add_component<Weapon>()->set_weapon(Weapons::enemy_weapons[type]);

        enemy_entity->add_component<MovingBehaviour>();

        // Entity for selector that appears above enemy when player_normal aims at
        auto selector_entity = Punity::PEntity::make_entity(Game::Names::SELECTOR, enemy_entity, false);

        selector_entity->get_transform()->set_local({0, -8});
        selector_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::enemy_selected_arrow, Game::Sprites::Layers::SELECTOR)
        );

        return enemy_entity;
    }


    Punity::PEntity* make_player_bullet(Punity::PEntity* parent, uint8_t projectile_type) {
        auto bullet_entity = Punity::PEntity::make_entity(Game::Names::PLAYER_BULLET, parent, true);

        // Set sprite according to projectile type
        auto collider = bullet_entity->add_component<Punity::Components::PCircleCollider>();

        switch (projectile_type) {
            // For each projectile, set the sprite and set the according size for the circle collider
            case Colliders::PLAYER_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::player_bullet_1, Game::Sprites::Layers::BULLET)
                );
                collider->set_radius(Game::Sprites::player_bullet_1_w / 2.0f);
                break;
            case Colliders::PLAYER_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::player_bullet_2, Game::Sprites::Layers::BULLET)
                );
                collider->set_radius(Game::Sprites::player_bullet_2_w / 2.0f);
                break;
            case Colliders::PLAYER_PROJECTILE_3:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::player_bullet_3, Game::Sprites::Layers::BULLET)
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
        auto bullet_entity = Punity::PEntity::make_entity(Game::Names::ENEMY_BULLET, parent, true);

        // Set sprite according to projectile type
        auto collider = bullet_entity->add_component<Punity::Components::PCircleCollider>();

        switch (projectile_type) {
            // For each projectile, set the sprite and set the according size for the circle collider
            case Colliders::ENEMY_PROJECTILE_1:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::enemy_bullet_1, Game::Sprites::Layers::BULLET)
                );
                collider->set_radius(Game::Sprites::enemy_bullet_1_w / 2.0f);
                break;
            case Colliders::ENEMY_PROJECTILE_2:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::enemy_bullet_2, Game::Sprites::Layers::BULLET)
                );
                collider->set_radius(Game::Sprites::enemy_bullet_2_w / 2.0f);
                break;
            case Colliders::ENEMY_PROJECTILE_3:
                bullet_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                        SPRITE(Game::Sprites::enemy_bullet_3, Game::Sprites::Layers::BULLET)
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
        auto gameplay_UI_entity = Punity::PEntity::make_entity(Game::Names::GAMEPLAY_UI, parent, true);

        // Hearts system
        auto hearts_entity = Punity::PEntity::make_entity(Game::Names::HEARTS, gameplay_UI_entity, true);
        auto heart1 = Punity::PEntity::make_entity(Game::Names::HEART1, hearts_entity, true);
        auto heart2 = Punity::PEntity::make_entity(Game::Names::HEART2, hearts_entity, true);
        auto heart3 = Punity::PEntity::make_entity(Game::Names::HEART3, hearts_entity, true);

        // Place and set hearts
        // Beware esoteric computations
        heart1->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                - 56.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::heart, Game::Sprites::Layers::HUD)
        );

        heart2->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                - 48.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::heart, Game::Sprites::Layers::HUD)
        );

        heart3->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                - 40.0f + Game::Sprites::heart_w * 0.5f,
                - 64.0f + Game::Sprites::heart_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::heart, Game::Sprites::Layers::HUD)
        );

        // Energy counting system
        auto energy_hud_entity = Punity::PEntity::make_entity(Game::Names::ENERGY_HUD, gameplay_UI_entity, true);
        auto energy_image = Punity::PEntity::make_entity(Game::Names::ENERGY_IMG, energy_hud_entity, true);

        energy_image->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                54.0f - Game::Sprites::energy_w * 0.5f,
                - 64.0f + Game::Sprites::energy_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::energy, Game::Sprites::Layers::HUD)
        );

        auto energy_digit_1 = Punity::PEntity::make_entity(Game::Names::ENERGY_DIGIT_1, energy_hud_entity, true);
        auto energy_digit_2 = Punity::PEntity::make_entity(Game::Names::ENERGY_DIGIT_2, energy_hud_entity, true);

        energy_digit_1->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                40.0f - Game::Sprites::nine_w * 0.5f,
                - 65.0f + Game::Sprites::nine_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::nine, Game::Sprites::Layers::HUD)
        );

        energy_digit_2->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                48.0f - Game::Sprites::nine_w * 0.5f,
                - 65.0f + Game::Sprites::nine_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::nine, Game::Sprites::Layers::HUD)
        );

        // Level - stage hud
        auto counter_entity = Punity::PEntity::make_entity(Game::Names::COUNTER, gameplay_UI_entity, true);
        auto level_counter_entity = Punity::PEntity::make_entity(Game::Names::LEVEL_COUNTER, counter_entity, true);
        auto dash_entity = Punity::PEntity::make_entity(Game::Names::DASH_CHARACTER, counter_entity, true);
        auto stage_counter_entity = Punity::PEntity::make_entity(Game::Names::STAGE_COUNTER, counter_entity, true);

        level_counter_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                - 11.0f + Game::Sprites::one_w * 0.5f,
                - 65.0f + Game::Sprites::one_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::one, Game::Sprites::Layers::HUD)
        );

        dash_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                0,
                - 63.0f + Game::Sprites::dash_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::dash, Game::Sprites::Layers::HUD)
        );

        stage_counter_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_ui_pos({
                12.0f - Game::Sprites::one_w * 0.5f,
                - 65.0f + Game::Sprites::one_h * 0.5f
        })->set_sprite(
                SPRITE(Game::Sprites::one, Game::Sprites::Layers::HUD)
        );


        // Selected weapon hud
        auto weapon_status_entity = Punity::PEntity::make_entity(Game::Names::WEAPON_STATUS_UI, gameplay_UI_entity, true);
        auto arrow_entity = Punity::PEntity::make_entity(Game::Names::WEAPON_STATUS_ARROW, weapon_status_entity, true);
        arrow_entity->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
         0,
         63.0f - Game::Sprites::arrow_left_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::arrow_left, Game::Sprites::Layers::HUD)
        );

        // Make Default weapon energy, energy counter, damage, damage counter
        auto default_weapon_entity = Punity::PEntity::make_entity(Game::Names::DEFAULT_WEAPON, weapon_status_entity, true);
        auto default_weapon_energy = Punity::PEntity::make_entity(Game::Names::DEFAULT_WEAPON_ENERGY_IMG, default_weapon_entity, true);
        auto default_weapon_energy_counter = Punity::PEntity::make_entity(Game::Names::DEFAULT_WEAPON_ENERGY_CNT, default_weapon_entity, true);
        auto default_weapon_attack = Punity::PEntity::make_entity(Game::Names::DEFAULT_WEAPON_ATTACK_IMG, default_weapon_entity, true);
        auto default_weapon_attack_counter = Punity::PEntity::make_entity(Game::Names::DEFAULT_WEAPON_ATTACK_CNT, default_weapon_entity, true);

        default_weapon_energy_counter->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
             -65.0f + 16.0f + Game::Sprites::zero_w / 2.0f,
             63.0f - Game::Sprites::zero_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::zero, Game::Sprites::Layers::HUD)
        );

        default_weapon_energy->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 -64.0f + 24.0f + Game::Sprites::energy_w / 2.0f,
                 62.0f - Game::Sprites::energy_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::energy, Game::Sprites::Layers::HUD)
        );


        default_weapon_attack_counter->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 -65.0f + 36.0f + Game::Sprites::one_w / 2.0f,
                 63.0f - Game::Sprites::one_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::one, Game::Sprites::Layers::HUD)
        );

        default_weapon_attack->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 -64.0f + 44.0f + Game::Sprites::sword_w / 2.0f,
                 63.0f - Game::Sprites::sword_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::sword, Game::Sprites::Layers::HUD)
        );


        // Make Equipped weapon energy, energy counter, damage, damage counter but have it inactive
        auto equipped_weapon_entity = Punity::PEntity::make_entity(Game::Names::EQUIPPED_WEAPON, weapon_status_entity, false);
        auto equipped_weapon_energy = Punity::PEntity::make_entity(Game::Names::EQUIPPED_WEAPON_ENERGY_IMG, equipped_weapon_entity, true);
        auto equipped_weapon_energy_counter = Punity::PEntity::make_entity(Game::Names::EQUIPPED_WEAPON_ENERGY_CNT, equipped_weapon_entity, true);
        auto equipped_weapon_attack = Punity::PEntity::make_entity(Game::Names::EQUIPPED_WEAPON_ATTACK_IMG, equipped_weapon_entity, true);
        auto equipped_weapon_attack_counter = Punity::PEntity::make_entity(Game::Names::EQUIPPED_WEAPON_ATTACK_CNT, equipped_weapon_entity, true);

        equipped_weapon_energy_counter->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 12.0f + Game::Sprites::zero_w / 2.0f,
                 63.0f - Game::Sprites::zero_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::zero, Game::Sprites::Layers::HUD)
        );

        equipped_weapon_energy->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 20.0f + Game::Sprites::energy_w / 2.0f,
                 62.0f - Game::Sprites::energy_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::energy, Game::Sprites::Layers::HUD)
        );


        equipped_weapon_attack_counter->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 30.0f + Game::Sprites::one_w / 2.0f,
                 63.0f - Game::Sprites::one_h / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::one, Game::Sprites::Layers::HUD)
        );

        equipped_weapon_attack->add_component<Punity::Components::PUISpriteRenderer>()
        ->set_ui_pos({
                 38.0f + Game::Sprites::sword_h / 2.0f,
                 63.0f - Game::Sprites::sword_w / 2.0f
        })
        ->set_sprite(
                SPRITE(Game::Sprites::sword, Game::Sprites::Layers::HUD)
        );

        return gameplay_UI_entity;
    }

    Punity::PEntity* make_energy_pickup(Punity::PEntity* parent) {
        auto energy_pickup_entity = Punity::PEntity::make_entity(Game::Names::ENERGY_PICKUP, parent, true);

        energy_pickup_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::energy, Game::Sprites::Layers::PICKUP)
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
        auto heart_pickup_entity = Punity::PEntity::make_entity(Game::Names::HEART_PICKUP, parent, true);

        heart_pickup_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::heart, Game::Sprites::Layers::PICKUP)
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

    Punity::PEntity* make_weapon_pickup(Punity::PEntity* parent, Weapons::WeaponConfig config, bool is_rare) {
        auto weapon_entity = Punity::PEntity::make_entity(Game::Names::WEAPON_PICKUP, parent, true);

        if (is_rare)
            weapon_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::rare_sword, Game::Sprites::Layers::PICKUP)
            );
        else
            weapon_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::sword, Game::Sprites::Layers::PICKUP)
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