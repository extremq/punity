//
// Created by god on 17.12.2022.
//

#include "ChestBehaviour.h"
#include "GameplayPrefabCreator.h"
#include "game/Assets/weapons.h"

namespace Game {
    void ChestBehaviour::on_enable() {
        // Let's see what the player will get
        float random_chance = Punity::Utils::random();

        if (random_chance < 0.0030f) {
            // 30% for 15 energy
            GameplayPrefabCreator::drop_energy_pickups(Punity::Engine.find_entity("Room"),
                                                       5,
                                                       get_entity()->get_transform()->global_position);
        }
        else if (random_chance < 0.0080f) {
            // 50% for 1 heart
            GameplayPrefabCreator::drop_heart_pickups(Punity::Engine.find_entity("Room"),
                                                      1,
                                                      get_entity()->get_transform()->global_position);
        }
        else {
            // 20% for weapon!!! OMG
            GameplayPrefabCreator::make_weapon_pickup(Punity::Engine.find_entity("Room"),
                                                      Weapons::rifle);
        }
    }
} // Game