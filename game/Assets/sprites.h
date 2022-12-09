#ifndef _SPRITES_
#define _SPRITES_

#include <cstdint>

namespace Game::Sprites {
    
	extern uint16_t const game_title_start [35 * 8];
	extern bool const game_title_start_alpha [35 * 8];
	extern uint16_t const game_title_start_w;
	extern uint16_t const game_title_start_h;
	extern uint16_t const level3 [20 * 20];
	extern bool const level3_alpha [20 * 20];
	extern uint16_t const level3_w;
	extern uint16_t const level3_h;
	extern uint16_t const level2 [20 * 20];
	extern bool const level2_alpha [20 * 20];
	extern uint16_t const level2_w;
	extern uint16_t const level2_h;
	extern uint16_t const wall [8 * 8];
	extern bool const wall_alpha [8 * 8];
	extern uint16_t const wall_w;
	extern uint16_t const wall_h;
	extern uint16_t const chest [16 * 8];
	extern bool const chest_alpha [16 * 8];
	extern uint16_t const chest_w;
	extern uint16_t const chest_h;
	extern uint16_t const game_title [46 * 16];
	extern bool const game_title_alpha [46 * 16];
	extern uint16_t const game_title_w;
	extern uint16_t const game_title_h;
	extern uint16_t const player [8 * 8];
	extern bool const player_alpha [8 * 8];
	extern uint16_t const player_w;
	extern uint16_t const player_h;
	extern uint16_t const level1 [20 * 20];
	extern bool const level1_alpha [20 * 20];
	extern uint16_t const level1_w;
	extern uint16_t const level1_h;

}

#endif