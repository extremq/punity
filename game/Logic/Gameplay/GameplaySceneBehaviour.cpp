//
// Created by god on 05.12.2022.
//

#include "GameplaySceneBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "game/Logic/Gameplay/GameplayPrefabCreator.h"
#include "PlayerBehaviour.h"

namespace Game {
    void GameplaySceneBehaviour::on_update() {
        if (player != nullptr && !scene_ended) {
            auto player_behaviour = player->get_component<PlayerBehaviour>();
            if (!player_behaviour->is_alive()) {
                scene_ended = true;
                // We are dead
                // TODO make a death thingy? Use invokes.
                SceneManager::reset_progress();
                SceneManager::switch_scene(START_SCENE);
            }
            else if (player_behaviour->has_touched_chest()) {
                scene_ended = true;
                // Player touched chest go to next level i guess?
                // TODO should only increment stage, actually
                SceneManager::level = std::max(1, (SceneManager::level + 1) % 4);
                SceneManager::switch_scene(LEVEL_LOAD_SCENE);
            }
        }
    }

    // When this is enabled, setup the level!
    // Only enabled/disabled when entering from
    // Loading screens
    void GameplaySceneBehaviour::on_enable() {
        setup_scene();
    }

    // Room and players are made once since they need to remain in memory
    // Everything else is a child of room. Children of room get destroyed
    // each load.
    void GameplaySceneBehaviour::setup_scene() {
        scene_ended = false;

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

        // Show the player with a delay of 1 second
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::show_player,
                this,
                PLAYER_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );

        // Make the enemies with a delay of 2 seconds
        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
                &GameplaySceneBehaviour::make_enemies_entity_and_show_it,
                this,
                ENEMY_CREATION_DELAY_SECONDS,
                get_entity()->get_id()
        );

        // TODO remove this
//        new Punity::Utils::PInvokable<GameplaySceneBehaviour>(
//                &GameplaySceneBehaviour::make_chest_and_show_it,
//                this,
//                ENEMY_CREATION_DELAY_SECONDS + 3.0,
//                get_entity()->get_id()
//        );
    }

    void GameplaySceneBehaviour::show_player() {
        player->set_active(true);
        player->get_transform()->set_global({0, -40});
    }

    void GameplaySceneBehaviour::make_chest_and_show_it() {
        GameplayPrefabCreator::make_chest(room);
    }

    void GameplaySceneBehaviour::make_enemies_entity_and_show_it() {
        // Create parent entity
        enemies = GameplayPrefabCreator::make_enemies_entity(room);

        make_enemies();
        place_enemies();
    }

    void GameplaySceneBehaviour::make_enemies() {
        // Create enemies and store them
        // TODO play with difficulty
        enemy[0] = GameplayPrefabCreator::make_enemy(enemies);
        enemy[1] = GameplayPrefabCreator::make_enemy(enemies);
        enemy[2] = GameplayPrefabCreator::make_enemy(enemies);
    }

    void GameplaySceneBehaviour::place_enemies() {
        enemy[0]->get_transform()->set_global({0, 40});
        enemy[1]->get_transform()->set_global({40, 0});
        enemy[2]->get_transform()->set_global({-40, 0});
    }

} // Game