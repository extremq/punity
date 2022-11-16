//
// Created by god on 15.11.2022.
//

#ifndef PUNITY_GAME_ENGINE_TESTCOMPONENT_H
#define PUNITY_GAME_ENGINE_TESTCOMPONENT_H

#include "PComponent.h"

namespace Punity::Components {
    class testComponent : public PComponent {
        void on_update() override;
        void on_destroy() override;
    };

}


#endif //PUNITY_GAME_ENGINE_TESTCOMPONENT_H
