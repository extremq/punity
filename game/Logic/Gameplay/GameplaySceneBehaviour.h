//
// Created by god on 05.12.2022.
//

#ifndef _ROOM_H
#define _ROOM_H

#include "game/Logic/SceneManager.h"

constexpr float PLAYER_CREATION_DELAY_SECONDS = 1.0f;
constexpr float ENEMY_CREATION_DELAY_SECONDS = 2.5f;

namespace Game {

    // Handles gameplay mostly, since it's all contained in rooms
    // Also a state machine.
    class GameplaySceneBehaviour : public Punity::Components::PComponent {
    private:
        // Grouping entities
        Punity::PEntity* room = nullptr;
        Punity::PEntity* enemies = nullptr;
        Punity::PEntity* enemy[3] = {nullptr, nullptr, nullptr};

        // Player entity
        Punity::PEntity* player = nullptr;


        bool scene_ended = false;

        void on_update() override;
        void on_enable() override;

        // States
        void setup_scene();
        void show_player();
        void make_chest_and_show_it();
        void make_enemies_entity_and_show_it();
        void make_enemies();
        void place_enemies();

    public:
    };

} // Game

#endif //_ROOM_H
