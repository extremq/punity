//
// Created by god on 17.12.2022.
//

#include "ChestBehaviour.h"
#include "GameplayPrefabCreator.h"
#include "game/Assets/weapons.h"
#include "game/Assets/strings.h"

namespace Game {
    void ChestBehaviour::on_enable() {
        // Let's see what the player will get
        float random_chance = Punity::Utils::random();

        if (random_chance < 0.0030f) {
            // 30% for 15 energy
            GameplayPrefabCreator::drop_energy_pickups(Punity::Engine.find_entity(Game::Names::ROOM),
                                                       5,
                                                       get_entity()->get_transform()->global_position);
        }
        else if (random_chance < 0.0080f) {
            // 50% for 1 heart
            GameplayPrefabCreator::drop_heart_pickups(Punity::Engine.find_entity(Game::Names::ROOM),
                                                      1,
                                                      get_entity()->get_transform()->global_position);
        }
        else {
            // 20% for weapon!!! OMG

            float weapon_choice = Punity::Utils::random();

            uint8_t weapon_number = std::floor(Punity::Utils::random(0, 2.99f));

            // 1/4 chance for rare weapon and level
            if (weapon_choice < 0.25f + (SceneManager::level - 1) * 0.25f) {
                GameplayPrefabCreator::make_weapon_pickup(Punity::Engine.find_entity(Game::Names::ROOM),
                                                          Weapons::rare_weapons[weapon_number], true);
            }
            else {
                GameplayPrefabCreator::make_weapon_pickup(Punity::Engine.find_entity(Game::Names::ROOM),
                                                          Weapons::common_weapons[weapon_number], false);
            }

        }
    }
} // Game