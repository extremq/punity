#include "sprites.h"

namespace Game::Sprites {

	uint16_t const game_title_start [35 * 8] = { 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0 };
	bool const game_title_start_alpha [35 * 8] = { false, false, false, false, true, true, true, true, true, false, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, false, false, false, false, true, false, false, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, true, true, true, false, false, true, true, false, false, false, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, true, true, false, true, true, false, false, true, true, true, false, false, false, true, true, false, false, true, true, true, true, true, false, true, true, true, true, false, false, false, true, true, false, false, true, true, false, false, true, true, false, false, false, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, false, false, false, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, true, true, true, false, false, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, true, false, false, false, false, true, true, true, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, false };
	uint16_t const game_title_start_w = 35;
	uint16_t const game_title_start_h = 8;
	uint16_t const first_enemy_type [8 * 8] = { 0x0, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x0, 0x7bef, 0x7bef, 0x0, 0x0, 0x0, 0x0, 0x7bef, 0x7bef, 0x7bef, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7bef, 0x7bef, 0xa514, 0x0, 0x0, 0x0, 0x0, 0xa514, 0x7bef, 0x0, 0xa514, 0x0, 0x0, 0x0, 0x0, 0xa514, 0x0, 0x0, 0xa514, 0xc618, 0x0, 0x0, 0xc618, 0xa514, 0x0, 0x0, 0x0, 0xc618, 0xc618, 0xc618, 0xc618, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc618, 0xc618, 0x0, 0x0, 0x0 };
	bool const first_enemy_type_alpha [8 * 8] = { false, true, true, true, true, true, true, false, true, true, false, false, false, false, true, true, true, false, false, false, false, false, false, true, true, true, false, false, false, false, true, true, false, true, false, false, false, false, true, false, false, true, true, false, false, true, true, false, false, false, true, true, true, true, false, false, false, false, false, true, true, false, false, false };
	uint16_t const first_enemy_type_w = 8;
	uint16_t const first_enemy_type_h = 8;
	uint16_t const level3 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level3_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, false, true, false, false, false, false, false, false, false, false, false, false, true, false, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, false, false, false, false, true, true, true, true, true, true, false, false, false, false, true, false, true, true, false, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, false, true, true, true, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, true, true, true, false, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, false, true, true, true, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, true, true, true, false, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, false, true, true, false, true, false, false, false, false, true, true, true, true, true, true, false, false, false, false, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, false, true, false, false, false, false, false, false, false, false, false, false, true, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level3_w = 20;
	uint16_t const level3_h = 20;
	uint16_t const level2 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level2_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, true, true, true, false, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, true, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, true, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level2_w = 20;
	uint16_t const level2_h = 20;
	uint16_t const wall [8 * 8] = { 0x632c, 0x632c, 0x8410, 0x8410, 0x632c, 0x8410, 0x8410, 0x8410, 0x4a69, 0x8410, 0x632c, 0x8410, 0x8410, 0x632c, 0x632c, 0x632c, 0x8410, 0x8410, 0xb596, 0x9cd3, 0x9cd3, 0x8410, 0x4a69, 0x4a69, 0x632c, 0x8410, 0x9cd3, 0x8410, 0x8410, 0x9cd3, 0x8410, 0x8410, 0x8410, 0x8410, 0x632c, 0x8410, 0x632c, 0x632c, 0x8410, 0x8410, 0xb596, 0x632c, 0x8410, 0x632c, 0x4a69, 0x8410, 0xb596, 0x9cd3, 0x9cd3, 0xb596, 0x8410, 0x8410, 0x8410, 0x9cd3, 0x9cd3, 0x8410, 0x8410, 0x9cd3, 0x8410, 0x8410, 0x9cd3, 0x8410, 0x8410, 0x8410 };
	bool const wall_alpha [8 * 8] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const wall_w = 8;
	uint16_t const wall_h = 8;
	uint16_t const chest [16 * 8] = { 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xc618, 0xa514, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xbbca, 0xbbca, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xc618, 0xa514, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xa514, 0xa514, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xbbca, 0xbbca, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xbbca, 0xbbca, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xf54f, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca, 0xbbca };
	bool const chest_alpha [16 * 8] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const chest_w = 16;
	uint16_t const chest_h = 8;
	uint16_t const enemy_selected_arrow [6 * 3] = { 0xc024, 0xc024, 0xc024, 0xc024, 0xc024, 0xc024, 0xfe41, 0xc024, 0xc024, 0xc024, 0xc024, 0xfe41, 0x0, 0xfe41, 0xfe41, 0xfe41, 0xfe41, 0x0 };
	bool const enemy_selected_arrow_alpha [6 * 3] = { true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, false };
	uint16_t const enemy_selected_arrow_w = 6;
	uint16_t const enemy_selected_arrow_h = 3;
	uint16_t const enemy_bullet [3 * 3] = { 0x0, 0xe8e4, 0x0, 0xe8e4, 0xff80, 0xe8e4, 0x0, 0xe8e4, 0x0 };
	bool const enemy_bullet_alpha [3 * 3] = { false, true, false, true, true, true, false, true, false };
	uint16_t const enemy_bullet_w = 3;
	uint16_t const enemy_bullet_h = 3;
	uint16_t const game_title [46 * 16] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const game_title_alpha [46 * 16] = { true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true };
	uint16_t const game_title_w = 46;
	uint16_t const game_title_h = 16;
	uint16_t const player_bullet [3 * 3] = { 0x0, 0x3a59, 0x0, 0x3a59, 0x9edd, 0x3a59, 0x0, 0x3a59, 0x0 };
	bool const player_bullet_alpha [3 * 3] = { false, true, false, true, true, true, false, true, false };
	uint16_t const player_bullet_w = 3;
	uint16_t const player_bullet_h = 3;
	uint16_t const player [8 * 8] = { 0x0, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0x0, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0x8802, 0xe8e4, 0xe8e4, 0x8802, 0xe8e4, 0xe8e4, 0xe8e4, 0xc024, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xc024, 0xe8e4, 0xe8e4, 0xe8e4, 0x8802, 0xffff, 0xffff, 0x8802, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0x8802, 0x8802, 0xe8e4, 0xe8e4, 0xe8e4, 0x0, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0xe8e4, 0x0 };
	bool const player_alpha [8 * 8] = { false, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, false };
	uint16_t const player_w = 8;
	uint16_t const player_h = 8;
	uint16_t const level1 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level1_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level1_w = 20;
	uint16_t const level1_h = 20;

}