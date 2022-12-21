//
// Created by god on 05.12.2022.
//

#include "GameplaySceneBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "game/Logic/Gameplay/GameplayPrefabCreator.h"
#include "PlayerBehaviour.h"
#include "GameplaySceneManager.h"
#include "game/Assets/sprite_layers.h"
#include "game/Assets/groupings.h"
#include "game/Assets/strings.h"
#include "RoomBehaviour.h"

namespace Game {
    void GameplaySceneBehaviour::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        auto player_behaviour = player->get_component<PlayerBehaviour>();
        auto player_actor_behaviour = player->get_component<ActorBehaviour>();

        if (GameplaySceneManager::enemies_loaded)
            for (size_t i = 0; i < enemy.size(); ++i) {
                // Check and destroy dead enemies
                // Also set nullptr
                if (enemy_actor_behaviour[i] != nullptr && enemy_actor_behaviour[i]->is_dead()) {
                    enemy[i]->destroy();
                    enemy[i] = nullptr;
                    enemy_actor_behaviour[i] = nullptr;
                }
            }

        // Update the hearts to reflect current player health
        update_hearts(player_actor_behaviour);

        // Update weapon status
        update_weapon_status(player_behaviour);

        // Update energy
        update_energy(player_behaviour);

        // Update the level and stage
        update_level_stage_counter();

        bool enemies_are_dead = enemies->get_children_count() == 0;

        // Check if player is dead
        if (player_actor_behaviour->is_dead()) {
            // TODO make a death thingy? Use invokes.
            player_behaviour->fully_reset_player();

            // GO back to start
            SceneManager::reset_progress();
            SceneManager::switch_scene(START_SCENE);
        } else if (enemies_are_dead && GameplaySceneManager::enemies_loaded) {
            // Mark as unloaded
            GameplaySceneManager::enemies_loaded = false;

            // Player finished this wave
            if (wave == MAX_WAVE) {
                // Finished stage
                // Show the chest and move on
                new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                        &GameplaySceneBehaviour::make_chest_and_show_it,
                        this,
                        ENEMY_CREATION_DELAY_SECONDS,
                        get_entity()->get_id()
                );
            } else {
                // Load next wave
                wave++;

                // Make new enemies with a delay
                new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                        &GameplaySceneBehaviour::make_enemies,
                        this,
                        MIDGAME_ENEMY_CREATION_DELAY_SECONDS,
                        get_entity()->get_id()
                );
            }
        } else if (player_behaviour->has_touched_chest() && GameplaySceneManager::chest_loaded) {
            // Make it once!
            GameplaySceneManager::chest_loaded = false;
            GameplaySceneManager::player_loaded = false;
            GameplaySceneManager::enemies_loaded = false;

            // Reset wave level
            wave = 1;

            if (SceneManager::stage == MAX_STAGE) {
                // NOW we switch level
                SceneManager::level = std::max(1, (SceneManager::level + 1) % (MAX_LEVEL + 1));
                SceneManager::stage = 1;
                SceneManager::switch_scene(LEVEL_LOAD_SCENE);
            } else {
                SceneManager::stage++;

                // Disable things temporarily
                room->set_active(false);
                player->set_active(false);
                hud->set_active(false);

                for (size_t i = 0; i < enemy.size(); ++i) {
                    enemy_actor_behaviour[i] = nullptr;
                    enemy[i] = nullptr;
                }

                // Make new stage
                new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                        &GameplaySceneBehaviour::setup_stage,
                        this,
                        STAGE_SWITCH_DELAY_SECONDS,
                        get_entity()->get_id()
                );
            }
        }
    }

    // When this is enabled, setup the level!
    // Only enabled/disabled when entering start
    void GameplaySceneBehaviour::on_enable() {
        wave = 1;

        if (SceneManager::level == 1 && player != nullptr) {
            // Reset player health
            player->get_component<ActorBehaviour>()->replenish_hitpoints();
        }

        // Reset scene status
        GameplaySceneManager::player_loaded = false;
        GameplaySceneManager::enemies_loaded = false;
        GameplaySceneManager::chest_loaded = false;

        setup_scene();
        setup_stage();
    }

    // Room and players are made once since they need to remain in memory
    // Everything else is a child of room. Children of room get destroyed
    // each load.
    void GameplaySceneBehaviour::setup_stage() {
        // Reset stage status
        room->set_active(true);

        // Show the player and hud later
        player->set_active(false);
        hud->set_active(false);

        // Create enemies entity (it's deleted each time)
        enemies = GameplayPrefabCreator::make_enemies_entity(room);

        // Show the player with a delay of 1 second
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::show_player,
                this,
                PLAYER_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );

        // Make the enemies with a delay of 2 seconds
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::make_enemies,
                this,
                ENEMY_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );
    }

    void GameplaySceneBehaviour::show_player() {
        // Show the player-related things
        player->set_active(true);
        hud->set_active(true);

        // Place player
        player->get_transform()->set_global(room->get_component<RoomBehaviour>()->get_player_starting_position());

        GameplaySceneManager::player_loaded = true;
    }

    void GameplaySceneBehaviour::make_chest_and_show_it() {
        GameplayPrefabCreator::make_chest(room);
        GameplaySceneManager::chest_loaded = true;
    }

    void GameplaySceneBehaviour::make_enemies() {
        // Create the enemies needed.
        setup_enemies();

        // Enemies are placed and ready to go
        GameplaySceneManager::enemies_loaded = true;
    }

    void GameplaySceneBehaviour::setup_scene() {
        if (hud == nullptr) {
            hud = GameplayPrefabCreator::make_gameplay_UI(get_entity());
        }

        if (player == nullptr) {
            player = GameplayPrefabCreator::make_player(get_entity());
        }

        // Make room and actors entities to group the tiles and the enemies
        if (room == nullptr) {
            room = GameplayPrefabCreator::make_room(get_entity());
        }
    }

    void GameplaySceneBehaviour::update_hearts(ActorBehaviour* player_actor) {
        if (!GameplaySceneManager::player_loaded) return;

        // Get heart entities
        uint8_t player_hitpoints = player_actor->get_hitpoints();
        auto hearts = hud->get_child_by_name(Game::Names::HEARTS);
        auto heart1 = hearts->get_child_by_name(Game::Names::HEART1);
        auto heart2 = hearts->get_child_by_name(Game::Names::HEART2);
        auto heart3 = hearts->get_child_by_name(Game::Names::HEART3);

        heart1->set_active(false);
        heart2->set_active(false);
        heart3->set_active(false);

        if (player_hitpoints >= 1) {
            heart1->set_active(true);
        }

        if (player_hitpoints >= 2) {
            heart2->set_active(true);
        }

        if (player_hitpoints >= 3) {
            heart3->set_active(true);
        }
    }

    void GameplaySceneBehaviour::update_energy(PlayerBehaviour *player_behaviour) {
        if (!GameplaySceneManager::player_loaded) return;

        // Change digits
        uint8_t player_energy = player_behaviour->get_remaining_energy();
        auto first_digit = hud->get_child_by_name(Game::Names::ENERGY_HUD)
                ->get_child_by_name(Game::Names::ENERGY_DIGIT_1)
                ->get_component<Punity::Components::PUISpriteRenderer>();
        auto second_digit = hud->get_child_by_name(Game::Names::ENERGY_HUD)
                ->get_child_by_name(Game::Names::ENERGY_DIGIT_2)
                ->get_component<Punity::Components::PUISpriteRenderer>();

        // Set first digit
        first_digit->set_sprite(
                Game::Groupings::numbers[player_energy / 10],
                Game::Groupings::numbers_alpha[player_energy / 10],
                Game::Groupings::numbers_h[player_energy / 10],
                Game::Groupings::numbers_w[player_energy / 10],
                Game::Sprites::Layers::HUD
                );

        // Set second digit
        second_digit->set_sprite(
                Game::Groupings::numbers[player_energy % 10],
                Game::Groupings::numbers_alpha[player_energy % 10],
                Game::Groupings::numbers_h[player_energy % 10],
                Game::Groupings::numbers_w[player_energy % 10],
                Game::Sprites::Layers::HUD
        );
    }

    void GameplaySceneBehaviour::update_level_stage_counter() {
        auto counter = hud->get_child_by_name(Game::Names::COUNTER);
        auto level_counter = counter->get_child_by_name(Game::Names::LEVEL_COUNTER)
                ->get_component<Punity::Components::PUISpriteRenderer>();
        auto stage_counter = counter->get_child_by_name(Game::Names::STAGE_COUNTER)
                ->get_component<Punity::Components::PUISpriteRenderer>();

        // Set the level
        level_counter->set_sprite(
                Game::Groupings::numbers[SceneManager::level],
                Game::Groupings::numbers_alpha[SceneManager::level],
                Game::Groupings::numbers_h[SceneManager::level],
                Game::Groupings::numbers_w[SceneManager::level],
                Game::Sprites::Layers::HUD
        );

        // Set the level
        stage_counter->set_sprite(
                Game::Groupings::numbers[SceneManager::stage],
                Game::Groupings::numbers_alpha[SceneManager::stage],
                Game::Groupings::numbers_h[SceneManager::stage],
                Game::Groupings::numbers_w[SceneManager::stage],
                Game::Sprites::Layers::HUD
        );
    }

    void GameplaySceneBehaviour::update_weapon_status(PlayerBehaviour *player_behaviour) {
        if (!GameplaySceneManager::player_loaded) return;

        auto weapon_status = hud->get_child_by_name(Game::Names::WEAPON_STATUS_UI);
        auto arrow = weapon_status->get_child_by_name(Game::Names::WEAPON_STATUS_ARROW);
        auto equipped_weapon = weapon_status->get_child_by_name(Game::Names::EQUIPPED_WEAPON);

        // Set arrow direction
        if (player_behaviour->is_using_starting_weapon()) {
            arrow->get_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                    SPRITE(Game::Sprites::arrow_left, Game::Sprites::Layers::HUD)
                    );
        }
        else {
            arrow->get_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                    SPRITE(Game::Sprites::arrow_right, Game::Sprites::Layers::HUD)
            );
        }

        // Only enable picked up weapons
        equipped_weapon->set_active(player_behaviour->has_picked_up_any_weapon());

        if (!player_behaviour->has_picked_up_any_weapon()) return;

        // Update picked up weapon
        auto eqp_weapon_energy_cnt = equipped_weapon->get_child_by_name(Game::Names::EQUIPPED_WEAPON_ENERGY_CNT);
        auto eqp_weapon_attack_cnt = equipped_weapon->get_child_by_name(Game::Names::EQUIPPED_WEAPON_ATTACK_CNT);
        auto config = player_behaviour->get_equipped_weapon();

        eqp_weapon_energy_cnt->get_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Groupings::numbers[config.energy_cost],
                Game::Groupings::numbers_alpha[config.energy_cost],
                Game::Groupings::numbers_h[config.energy_cost],
                Game::Groupings::numbers_w[config.energy_cost],
                Game::Sprites::Layers::HUD
                );

        eqp_weapon_attack_cnt->get_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Groupings::numbers[config.damage],
                Game::Groupings::numbers_alpha[config.damage],
                Game::Groupings::numbers_h[config.damage],
                Game::Groupings::numbers_w[config.damage],
                Game::Sprites::Layers::HUD
        );
    }

    void GameplaySceneBehaviour::setup_enemies() {
        clear_enemy_vectors();

        auto room_behaviour = room->get_component<RoomBehaviour>();

        for (uint8_t row = 2; row < 14; ++row) {
            for (uint8_t column = 2; column < 14; ++column) {
                if (room_behaviour->tiles[row][column] != ENEMY) continue;

                Punity::PEntity* temp_enemy;

                // Create a random enemy
                if (Punity::Utils::random() < 0.5f)
                    temp_enemy = GameplayPrefabCreator::make_enemy(enemies, (SceneManager::level - 1) * 3);
                else
                    temp_enemy = GameplayPrefabCreator::make_enemy(enemies, (SceneManager::level - 1) * 3 + 1);

                // Computations!!!
                temp_enemy->get_transform()->set_global({-64.0f + column * 8.0f + 4.0f, -64.0f + row * 8.0f + 4.0f});

                enemy.push_back(temp_enemy);
                enemy_actor_behaviour.push_back(temp_enemy->get_component<ActorBehaviour>());
            }
        }
    }

    void GameplaySceneBehaviour::clear_enemy_vectors() {
        enemy.clear();
        enemy_actor_behaviour.clear();
    }
} // Game