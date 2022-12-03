#ifndef _SPRITES_
#define _SPRITES_

#include <cstdint>

namespace Game::Sprites {
    
	extern uint16_t const player [8 * 8];
	extern bool const player_alpha [8 * 8];
	extern uint16_t const player_w;
	extern uint16_t const player_h;
	extern uint16_t const test_wall [8 * 8];
	extern bool const test_wall_alpha [8 * 8];
	extern uint16_t const test_wall_w;
	extern uint16_t const test_wall_h;
	extern uint16_t const test_text [64 * 8];
	extern bool const test_text_alpha [64 * 8];
	extern uint16_t const test_text_w;
	extern uint16_t const test_text_h;

}

#endif