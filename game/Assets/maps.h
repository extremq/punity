#ifndef _MAPS_
#define _MAPS_

#include <cstdint>

enum Tile {
    EMPTY,
    WALL,
    ENEMY,
    PORTAL,
    PLAYER,
    BOX,
    PRIZE
};

namespace Game::Maps {
    
	extern Tile const map1[12 * 12];
	extern Tile const map2[12 * 12];

}

#endif