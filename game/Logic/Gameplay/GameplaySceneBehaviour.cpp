//
// Created by god on 05.12.2022.
//

#include "GameplaySceneBehaviour.h"
#include "punity/Utils/PInvokable.h"
#include "game/Logic/Gameplay/GameplayPrefabCreator.h"
#include "PlayerBehaviour.h"
#include "GameplaySceneManager.h"
#include "game/Assets/sprite_layers.h"

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

        // Update the hearts to reflect current player health
        update_hearts(player_actor_behaviour);

        // Update energy
        update_energy(player_behaviour);

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

                for (size_t i = 0; i < 3; ++i) {
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

        // Reset all pointers
        for (size_t i = 0; i < 3; ++i) {
            enemy_actor_behaviour[i] = nullptr;
            enemy[i] = nullptr;
        }

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

        uint8_t player_hitpoints = player_actor->get_hitpoints();
        auto hearts = hud->get_child_by_name("Hearts");
        auto heart1 = hearts->get_child_by_name("Heart1");
        auto heart2 = hearts->get_child_by_name("Heart2");
        auto heart3 = hearts->get_child_by_name("Heart3");


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
        auto first_digit = hud->get_child_by_name("EnergyHUD")
                ->get_child_by_name("EnergyD1")
                ->get_component<Punity::Components::PUISpriteRenderer>();
        auto second_digit = hud->get_child_by_name("EnergyHUD")
                ->get_child_by_name("EnergyD2")
                ->get_component<Punity::Components::PUISpriteRenderer>();

        // Set first digit
        switch(player_energy / 10) {
            case 0:
                first_digit->set_sprite(
                        Game::Sprites::zero,
                        Game::Sprites::zero_alpha,
                        Game::Sprites::zero_h,
                        Game::Sprites::zero_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 1:
                first_digit->set_sprite(
                        Game::Sprites::one,
                        Game::Sprites::one_alpha,
                        Game::Sprites::one_h,
                        Game::Sprites::one_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 2:
                first_digit->set_sprite(
                        Game::Sprites::two,
                        Game::Sprites::two_alpha,
                        Game::Sprites::two_h,
                        Game::Sprites::two_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 3:
                first_digit->set_sprite(
                        Game::Sprites::three,
                        Game::Sprites::three_alpha,
                        Game::Sprites::three_h,
                        Game::Sprites::three_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 4:
                first_digit->set_sprite(
                        Game::Sprites::four,
                        Game::Sprites::four_alpha,
                        Game::Sprites::four_h,
                        Game::Sprites::four_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 5:
                first_digit->set_sprite(
                        Game::Sprites::five,
                        Game::Sprites::five_alpha,
                        Game::Sprites::five_h,
                        Game::Sprites::five_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 6:
                first_digit->set_sprite(
                        Game::Sprites::six,
                        Game::Sprites::six_alpha,
                        Game::Sprites::six_h,
                        Game::Sprites::six_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 7:
                first_digit->set_sprite(
                        Game::Sprites::seven,
                        Game::Sprites::seven_alpha,
                        Game::Sprites::seven_h,
                        Game::Sprites::seven_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 8:
                first_digit->set_sprite(
                        Game::Sprites::eight,
                        Game::Sprites::eight_alpha,
                        Game::Sprites::eight_h,
                        Game::Sprites::eight_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 9:
                first_digit->set_sprite(
                        Game::Sprites::nine,
                        Game::Sprites::nine_alpha,
                        Game::Sprites::nine_h,
                        Game::Sprites::nine_w,
                        Game::Sprites::Layers::HUD);
                break;
            default:
                break;
        }

        // Set second digit
        switch(player_energy % 10) {
            case 0:
                second_digit->set_sprite(
                        Game::Sprites::zero,
                        Game::Sprites::zero_alpha,
                        Game::Sprites::zero_h,
                        Game::Sprites::zero_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 1:
                second_digit->set_sprite(
                        Game::Sprites::one,
                        Game::Sprites::one_alpha,
                        Game::Sprites::one_h,
                        Game::Sprites::one_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 2:
                second_digit->set_sprite(
                        Game::Sprites::two,
                        Game::Sprites::two_alpha,
                        Game::Sprites::two_h,
                        Game::Sprites::two_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 3:
                second_digit->set_sprite(
                        Game::Sprites::three,
                        Game::Sprites::three_alpha,
                        Game::Sprites::three_h,
                        Game::Sprites::three_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 4:
                second_digit->set_sprite(
                        Game::Sprites::four,
                        Game::Sprites::four_alpha,
                        Game::Sprites::four_h,
                        Game::Sprites::four_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 5:
                second_digit->set_sprite(
                        Game::Sprites::five,
                        Game::Sprites::five_alpha,
                        Game::Sprites::five_h,
                        Game::Sprites::five_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 6:
                second_digit->set_sprite(
                        Game::Sprites::six,
                        Game::Sprites::six_alpha,
                        Game::Sprites::six_h,
                        Game::Sprites::six_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 7:
                second_digit->set_sprite(
                        Game::Sprites::seven,
                        Game::Sprites::seven_alpha,
                        Game::Sprites::seven_h,
                        Game::Sprites::seven_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 8:
                second_digit->set_sprite(
                        Game::Sprites::eight,
                        Game::Sprites::eight_alpha,
                        Game::Sprites::eight_h,
                        Game::Sprites::eight_w,
                        Game::Sprites::Layers::HUD);
                break;
            case 9:
                second_digit->set_sprite(
                        Game::Sprites::nine,
                        Game::Sprites::nine_alpha,
                        Game::Sprites::nine_h,
                        Game::Sprites::nine_w,
                        Game::Sprites::Layers::HUD);
                break;
            default:
                break;
        }

    }

} // Game