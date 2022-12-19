//
// Created by god on 06.12.2022.
//

#include "SceneCreator.h"
#include "game/Logic/UI/FloatingUI.h"
#include "game/Assets/sprites.h"
#include "game/Logic/Gameplay/LoadSceneBehaviour.h"
#include "game/Logic/Gameplay/StartSceneBehaviour.h"
#include "game/Logic/Gameplay/GameplaySceneBehaviour.h"
#include "game/Assets/sprite_layers.h"
#include "game/Assets/strings.h"

namespace Game::SceneCreator {
    Punity::PEntity* create_start_scene(Punity::PEntity* parent) {
        // Create the start screen
        auto start_scene_entity = Punity::PEntity::make_entity(Game::Names::START_SCENE, parent, false);
        start_scene_entity->add_component<StartSceneBehaviour>();

        // Make the pain logo
        auto pain_entity = Punity::PEntity::make_entity(Game::Names::PAIN_TEXT, start_scene_entity, true);

        pain_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::game_title, Game::Sprites::Layers::HUD)
        );

        // Make the start text
        auto start_entity = Punity::PEntity::make_entity(Game::Names::START_TEXT, start_scene_entity, true);

        // Make it floating!
        auto floater = start_entity->add_component<FloatingUI>();
        floater->scale = 5;
        floater->base_y = 20;

        start_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::game_title_start, Game::Sprites::Layers::HUD)
        );

        return start_scene_entity;
    }

    Punity::PEntity* create_loading_scene(Punity::PEntity* parent) {
        // Create the start screen
        auto load_scene_entity = Punity::PEntity::make_entity(Game::Names::LOAD_SCENE, parent, false);
        load_scene_entity->add_component<LoadSceneBehaviour>();

        // Create the digits
        auto digit_1_entity = Punity::PEntity::make_entity(Game::Names::LEVEL_1_IMG, true);
        auto digit_2_entity = Punity::PEntity::make_entity(Game::Names::LEVEL_2_IMG, true);
        auto digit_3_entity = Punity::PEntity::make_entity(Game::Names::LEVEL_3_IMG, true);

        // Set parent to load screen
        digit_1_entity->set_parent(load_scene_entity);
        digit_2_entity->set_parent(load_scene_entity);
        digit_3_entity->set_parent(load_scene_entity);

        // Set up sprites
        // They will be in the center by default.
        digit_1_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::level1, Game::Sprites::Layers::HUD)
        );
        digit_2_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::level2, Game::Sprites::Layers::HUD)
        );
        digit_3_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                SPRITE(Game::Sprites::level3, Game::Sprites::Layers::HUD)
        );
        return load_scene_entity;
    }

    Punity::PEntity* create_gameplay_scene(Punity::PEntity* parent) {
        // Create the gameplay scene
        auto gameplay_scene_entity = Punity::PEntity::make_entity(Game::Names::GAMEPLAY_SCENE, parent, false);
        gameplay_scene_entity->add_component<GameplaySceneBehaviour>();
        return gameplay_scene_entity;
    }

} // Game