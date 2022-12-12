//
// Created by god on 05.12.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include "game/Logic/SceneManager.h"
#include "ActorBehaviour.h"

constexpr float PLAYER_CREATION_DELAY_SECONDS = 1.0f;
constexpr float STAGE_SWITCH_DELAY_SECONDS = 1.0f;
constexpr float ENEMY_CREATION_DELAY_SECONDS = 2.0f;
constexpr float MIDGAME_ENEMY_CREATION_DELAY_SECONDS = 1.0f;

namespace Game {

    // Handles gameplay mostly, since it's all contained in rooms
    // Also a state machine.
    class GameplaySceneBehaviour : public Punity::Components::PComponent {
    private:
        // Grouping entities
        Punity::PEntity* room = nullptr;
        Punity::PEntity* enemies = nullptr;
        Punity::PEntity* enemy[3] = {nullptr, nullptr, nullptr};
        Game::ActorBehaviour* enemy_actor_behaviour[3] = {nullptr, nullptr, nullptr};

        // Player entity
        Punity::PEntity* player = nullptr;

        uint8_t wave = 1;

        bool scene_ended = false;
        bool scene_started = false;
        bool waves_ended = false;
        bool stage_switching = false;

        void on_update() override;
        void on_enable() override;

        // States
        void setup_stage();
        void show_player();
        void make_chest_and_show_it();
        void make_enemies_entity_and_show_it();
        void make_enemies();
        void place_enemies();
    public:
    };

} // Game

#endif //_ROOM_H
