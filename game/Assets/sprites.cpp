#include "sprites.h"

namespace Game::Sprites {

	uint16_t const placeholder_wall [8 * 8] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8802, 0x8802, 0xffff, 0x8802, 0x8802, 0x8802, 0x8802, 0xffff, 0x8802, 0x8802, 0xffff, 0x8802, 0xffff, 0xffff, 0x8802, 0xffff, 0x8802, 0x8802, 0xffff, 0x8802, 0xffff, 0xffff, 0x8802, 0xffff, 0x8802, 0x8802, 0xffff, 0x8802, 0x8802, 0x8802, 0x8802, 0xffff, 0x8802, 0x8802, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const placeholder_wall_alpha [8 * 8] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const placeholder_wall_w = 8;
	uint16_t const placeholder_wall_h = 8;
	uint16_t const game_title_start [35 * 8] = { 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0 };
	bool const game_title_start_alpha [35 * 8] = { false, false, false, false, true, true, true, true, true, false, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, false, false, false, false, true, false, false, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, true, true, true, false, false, true, true, false, false, false, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, true, true, false, true, true, false, false, true, true, true, false, false, false, true, true, false, false, true, true, true, true, true, false, true, true, true, true, false, false, false, true, true, false, false, true, true, false, false, true, true, false, false, false, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, false, false, false, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, true, true, true, false, false, false, true, true, false, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, true, false, false, false, false, true, true, true, true, true, false, false, true, true, false, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true, true, false, false, false, false, false };
	uint16_t const game_title_start_w = 35;
	uint16_t const game_title_start_h = 8;
	uint16_t const level3 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level3_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, false, true, false, false, false, false, false, false, false, false, false, false, true, false, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, false, false, false, false, true, true, true, true, true, true, false, false, false, false, true, false, true, true, false, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, false, true, true, true, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, true, true, true, false, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, false, true, true, true, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, true, true, true, false, false, true, false, true, true, true, true, false, false, true, true, true, true, false, true, false, false, true, true, false, true, false, false, false, false, true, true, true, true, true, true, false, false, false, false, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, false, true, false, false, false, false, false, false, false, false, false, false, true, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level3_w = 20;
	uint16_t const level3_h = 20;
	uint16_t const level2 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x0, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level2_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, true, true, true, false, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, false, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, true, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, true, true, true, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level2_w = 20;
	uint16_t const level2_h = 20;
	uint16_t const game_title [46 * 16] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const game_title_alpha [46 * 16] = { true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, true, true, true, true, false, false, true, true, true, true, false, false, true, true, true, true, true, true, true, true, false, false, true, true, true, true, false, false, false, false, true, true, true, true };
	uint16_t const game_title_w = 46;
	uint16_t const game_title_h = 16;
	uint16_t const level1 [20 * 20] = { 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802, 0x8802 };
	bool const level1_alpha [20 * 20] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, true, true, true, true, false, false, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
	uint16_t const level1_w = 20;
	uint16_t const level1_h = 20;

}