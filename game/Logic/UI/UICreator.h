//
// Created by god on 05.12.2022.
//

#ifndef _UICREATOR_H
#define _UICREATOR_H

#include "punity/Punity.h"
#include "FloatingUI.h"
#include "game/sprites.h"
#include "game/Logic/GameStateManager.h"

namespace Game::UICreator {
    static Punity::PEntity* create_start_screen() {
        // Get the game_manager component in order to communicate with it
        auto game_manager = GameStateManager::manager;

        // Create the start screen
        auto start_screen_entity = Punity::PEntity::make_entity("start_screen");
        start_screen_entity->set_parent(game_manager->UI);

        // Make the pain logo
        auto pain_entity = Punity::PEntity::make_entity("pain_text");
        pain_entity->set_parent(start_screen_entity);

        pain_entity->add_component<Punity::Components::PUISpriteRenderer>()->set_sprite(
                Game::Sprites::game_title,
                Game::Sprites::game_title_alpha,
                Game::Sprites::game_title_h,
                Game::Sprites::game_title_w,
                0
        );

        // Make the start text
        auto start_entity = Punity::PEntity::make_entity("start_text");
        start_entity->set_parent(start_screen_entity);

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

        start_screen_entity->set_active(false);
        return start_screen_entity;
    }

    static Punity::PEntity* create_loading_screen() {
        // Get the game_manager component in order to communicate with it
        auto game_manager = GameStateManager::manager;

        // Create the start screen
        auto load_screen_entity = Punity::PEntity::make_entity("load_screen");
        load_screen_entity->set_parent(game_manager->UI);

        // Create the digits
        auto digit_1_entity = Punity::PEntity::make_entity("1");
        auto digit_2_entity = Punity::PEntity::make_entity("2");
        auto digit_3_entity = Punity::PEntity::make_entity("3");

        // Set parent to load screen
        digit_1_entity->set_parent(load_screen_entity);
        digit_2_entity->set_parent(load_screen_entity);
        digit_3_entity->set_parent(load_screen_entity);

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

        load_screen_entity->set_active(false);
        return load_screen_entity;
    }

} // Game

#endif //_UICREATOR_H
