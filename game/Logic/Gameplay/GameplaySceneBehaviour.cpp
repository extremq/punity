//
// Created by god on 05.12.2022.
//

#include "GameplaySceneBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "game/Logic/Gameplay/GameplayPrefabCreator.h"
#include "PlayerBehaviour.h"
#include "GameplaySceneManager.h"

namespace Game {
    void GameplaySceneBehaviour::on_update() {
        if (!GameplaySceneManager::player_loaded) return;

        auto player_behaviour = player->get_component<PlayerBehaviour>();
        auto player_actor_behaviour = player->get_component<ActorBehaviour>();

        for (size_t i = 0; i < 3; ++i) {
            // Check and destroy dead enemies
            // Also set nullptr
            if (enemy_actor_behaviour[i] != nullptr && enemy_actor_behaviour[i]->is_dead()) {
                enemy[i]->destroy();
                enemy[i] = nullptr;
                enemy_actor_behaviour[i] = nullptr;
            }
        }

        bool enemies_are_dead = enemies->get_children_count() == 0;

        // Check if player is dead
        if (player_actor_behaviour->is_dead()) {
            // TODO make a death thingy? Use invokes.
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

            if (SceneManager::stage == MAX_STAGE) {
                // NOW we switch level
                SceneManager::level = std::max(1, (SceneManager::level + 1) % (MAX_LEVEL + 1));
                SceneManager::switch_scene(LEVEL_LOAD_SCENE);
            } else {
                SceneManager::stage++;

                // Disable things temporarily
                room->destroy();
                room = nullptr;

                for (size_t i = 0; i < 3; ++i) {
                    enemy_actor_behaviour[i] = nullptr;
                    enemy[i] = nullptr;
                }

                player->set_active(false);

                wave = 1;

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
    // Only enabled/disabled when entering from
    // Loading screens
    void GameplaySceneBehaviour::on_enable() {
        wave = 1;

        if (SceneManager::level == 1 && player != nullptr) {
            // Reset player health
            player->get_component<ActorBehaviour>()->set_hitpoints(6);
        }

        // Reset scene status
        GameplaySceneManager::player_loaded = false;
        GameplaySceneManager::enemies_loaded = false;
        GameplaySceneManager::chest_loaded = false;

        setup_stage();
    }

    // Room and players are made once since they need to remain in memory
    // Everything else is a child of room. Children of room get destroyed
    // each load.
    void GameplaySceneBehaviour::setup_stage() {
        // Reset stage status

        // Make room and actors entities to group the tiles and the enemies
        if (room == nullptr) {
            room = GameplayPrefabCreator::make_room(this->get_entity());
        }

        // This entity is the first state of our automata
        room->set_active(true);

        if (player == nullptr) {
            player = GameplayPrefabCreator::make_player(this->get_entity());
        }

        // Show the player at a later point
        player->set_active(false);

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
        player->set_active(true);
        GameplaySceneManager::player_loaded = true;
    }

    void GameplaySceneBehaviour::make_chest_and_show_it() {
        GameplayPrefabCreator::make_chest(room);
        GameplaySceneManager::chest_loaded = true;
    }

    void GameplaySceneBehaviour::make_enemies() {
        // Create enemies and store them
        // TODO play with difficulty
        enemy[0] = GameplayPrefabCreator::make_enemy(enemies);
        enemy[1] = GameplayPrefabCreator::make_enemy(enemies);
        enemy[2] = GameplayPrefabCreator::make_enemy(enemies);

        // Set behaviours so we don't use dynamic_cast on each frame
        enemy_actor_behaviour[0] = enemy[0]->get_component<ActorBehaviour>();
        enemy_actor_behaviour[1] = enemy[1]->get_component<ActorBehaviour>();
        enemy_actor_behaviour[2] = enemy[2]->get_component<ActorBehaviour>();

        place_enemies();

        // Enemies are placed and ready to go
        GameplaySceneManager::enemies_loaded = true;
    }

    void GameplaySceneBehaviour::place_enemies() {
        // TODO maybe play with their placement?
        enemy[0]->get_transform()->set_global({0, 40});
        enemy[1]->get_transform()->set_global({40, 0});
        enemy[2]->get_transform()->set_global({-40, 0});
    }

} // Game