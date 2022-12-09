//
// Created by god on 06.12.2022.
//

#include "SceneCreator.h"
#include "game/Logic/UI/FloatingUI.h"
#include "game/Assets/sprites.h"
#include "game/Logic/Gameplay/LoadSceneBehaviour.h"
#include "game/Logic/Gameplay/StartSceneBehaviour.h"
#include "game/Logic/Gameplay/GameplaySceneBehaviour.h"

namespace Game::SceneCreator {
    Punity::PEntity* create_start_scene(Punity::PEntity* parent) {
        // Create the start screen
        auto start_scene_entity = Punity::PEntity::make_entity("StartScene", parent, false);
        start_scene_entity->add_component<StartSceneBehaviour>();

        // Make the pain logo
        auto pain_entity = Punity::PEntity::make_entity("PainText", start_scene_entity, true);

        pain_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::game_title,
                Game::Sprites::game_title_alpha,
                Game::Sprites::game_title_h,
                Game::Sprites::game_title_w,
                0
        );

        // Make the start text
        auto start_entity = Punity::PEntity::make_entity("StartText", start_scene_entity, true);

        // Make it floating!
        auto floater = start_entity->add_component<FloatingUI>();
        floater->scale = 5;
        floater->base_y = 20;

        start_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::game_title_start,
                Game::Sprites::game_title_start_alpha,
                Game::Sprites::game_title_start_h,
                Game::Sprites::game_title_start_w,
                0
        );

        return start_scene_entity;
    }

    Punity::PEntity* create_loading_scene(Punity::PEntity* parent) {
        // Create the start screen
        auto load_scene_entity = Punity::PEntity::make_entity("LoadScene", parent, false);
        load_scene_entity->add_component<LoadSceneBehaviour>();

        // Create the digits
        auto digit_1_entity = Punity::PEntity::make_entity("1", true);
        auto digit_2_entity = Punity::PEntity::make_entity("2", true);
        auto digit_3_entity = Punity::PEntity::make_entity("3", true);

        // Set parent to load screen
        digit_1_entity->set_parent(load_scene_entity);
        digit_2_entity->set_parent(load_scene_entity);
        digit_3_entity->set_parent(load_scene_entity);

        // Set up sprites
        // They will be in the center by default.
        digit_1_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::level1,
                Game::Sprites::level1_alpha,
                Game::Sprites::level1_h,
                Game::Sprites::level1_w,
                0
        );
        digit_2_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::level2,
                Game::Sprites::level2_alpha,
                Game::Sprites::level2_h,
                Game::Sprites::level2_w,
                0
        );
        digit_3_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::level3,
                Game::Sprites::level3_alpha,
                Game::Sprites::level3_h,
                Game::Sprites::level3_w,
                0
        );
        return load_scene_entity;
    }

    Punity::PEntity* create_gameplay_scene(Punity::PEntity* parent) {
        // Create the gameplay scene
        auto gameplay_scene_entity = Punity::PEntity::make_entity("GameplayScene", parent, false);
        gameplay_scene_entity->add_component<GameplaySceneBehaviour>();
        return gameplay_scene_entity;
    }

} // Game