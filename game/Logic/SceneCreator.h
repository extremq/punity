//
// Created by god on 05.12.2022.
//

#ifndef _SCENECREATOR_H
#define _SCENECREATOR_H

#include "punity/Punity.h"

// Scene creator
// A singleton could've been used, but what purpose would it have?
// After all, this only has functions needed by the SceneManager once.
// I really don't need to waste RAM for a singleton.
// Let's not forget, singletons are a kind of static classes. If no encapsulation
// is needed, then really they should've been namespaces.
namespace Game::SceneCreator {
    Punity::PEntity* create_start_scene(Punity::PEntity* parent);
    Punity::PEntity* create_loading_scene(Punity::PEntity* parent);
    Punity::PEntity* create_gameplay_scene(Punity::PEntity* parent);
} // Game

#endif //_SCENECREATOR_H
