#ifndef _SPRITES_
#define _SPRITES_

#include <cstdint>

#define _MAKE_ALPHA(name) name##_alpha
#define MAKE_ALPHA(name) _MAKE_ALPHA(name)
#define _MAKE_W(name) name##_w
#define MAKE_W(name) _MAKE_W(name)
#define _MAKE_H(name) name##_h
#define MAKE_H(name) _MAKE_H(name)
#define SPRITE(name, layer) name, MAKE_ALPHA(name), MAKE_H(name), MAKE_W(name), layer

namespace Game::Sprites {
    
	extern uint16_t const arrow_left [8 * 8];
	extern bool const arrow_left_alpha [8 * 8];
	extern uint16_t const arrow_left_w;
	extern uint16_t const arrow_left_h;
	extern uint16_t const arrow_right [8 * 8];
	extern bool const arrow_right_alpha [8 * 8];
	extern uint16_t const arrow_right_w;
	extern uint16_t const arrow_right_h;
	extern uint16_t const bg_1 [8 * 8];
	extern bool const bg_1_alpha [8 * 8];
	extern uint16_t const bg_1_w;
	extern uint16_t const bg_1_h;
	extern uint16_t const bg_2 [8 * 8];
	extern bool const bg_2_alpha [8 * 8];
	extern uint16_t const bg_2_w;
	extern uint16_t const bg_2_h;
	extern uint16_t const bg_3 [8 * 8];
	extern bool const bg_3_alpha [8 * 8];
	extern uint16_t const bg_3_w;
	extern uint16_t const bg_3_h;
	extern uint16_t const chest [8 * 8];
	extern bool const chest_alpha [8 * 8];
	extern uint16_t const chest_w;
	extern uint16_t const chest_h;
	extern uint16_t const crate [8 * 8];
	extern bool const crate_alpha [8 * 8];
	extern uint16_t const crate_w;
	extern uint16_t const crate_h;
	extern uint16_t const dash [4 * 2];
	extern bool const dash_alpha [4 * 2];
	extern uint16_t const dash_w;
	extern uint16_t const dash_h;
	extern uint16_t const eight [7 * 8];
	extern bool const eight_alpha [7 * 8];
	extern uint16_t const eight_w;
	extern uint16_t const eight_h;
	extern uint16_t const enemy_1 [8 * 8];
	extern bool const enemy_1_alpha [8 * 8];
	extern uint16_t const enemy_1_w;
	extern uint16_t const enemy_1_h;
	extern uint16_t const enemy_2 [8 * 8];
	extern bool const enemy_2_alpha [8 * 8];
	extern uint16_t const enemy_2_w;
	extern uint16_t const enemy_2_h;
	extern uint16_t const enemy_3 [8 * 8];
	extern bool const enemy_3_alpha [8 * 8];
	extern uint16_t const enemy_3_w;
	extern uint16_t const enemy_3_h;
	extern uint16_t const enemy_4 [8 * 8];
	extern bool const enemy_4_alpha [8 * 8];
	extern uint16_t const enemy_4_w;
	extern uint16_t const enemy_4_h;
	extern uint16_t const enemy_5 [8 * 8];
	extern bool const enemy_5_alpha [8 * 8];
	extern uint16_t const enemy_5_w;
	extern uint16_t const enemy_5_h;
	extern uint16_t const enemy_6 [8 * 8];
	extern bool const enemy_6_alpha [8 * 8];
	extern uint16_t const enemy_6_w;
	extern uint16_t const enemy_6_h;
	extern uint16_t const enemy_bullet_1 [3 * 3];
	extern bool const enemy_bullet_1_alpha [3 * 3];
	extern uint16_t const enemy_bullet_1_w;
	extern uint16_t const enemy_bullet_1_h;
	extern uint16_t const enemy_bullet_2 [4 * 4];
	extern bool const enemy_bullet_2_alpha [4 * 4];
	extern uint16_t const enemy_bullet_2_w;
	extern uint16_t const enemy_bullet_2_h;
	extern uint16_t const enemy_bullet_3 [5 * 5];
	extern bool const enemy_bullet_3_alpha [5 * 5];
	extern uint16_t const enemy_bullet_3_w;
	extern uint16_t const enemy_bullet_3_h;
	extern uint16_t const enemy_selected_arrow [6 * 3];
	extern bool const enemy_selected_arrow_alpha [6 * 3];
	extern uint16_t const enemy_selected_arrow_w;
	extern uint16_t const enemy_selected_arrow_h;
	extern uint16_t const energy [6 * 6];
	extern bool const energy_alpha [6 * 6];
	extern uint16_t const energy_w;
	extern uint16_t const energy_h;
	extern uint16_t const five [7 * 8];
	extern bool const five_alpha [7 * 8];
	extern uint16_t const five_w;
	extern uint16_t const five_h;
	extern uint16_t const four [7 * 8];
	extern bool const four_alpha [7 * 8];
	extern uint16_t const four_w;
	extern uint16_t const four_h;
	extern uint16_t const game_title [46 * 16];
	extern bool const game_title_alpha [46 * 16];
	extern uint16_t const game_title_w;
	extern uint16_t const game_title_h;
	extern uint16_t const game_title_start [35 * 8];
	extern bool const game_title_start_alpha [35 * 8];
	extern uint16_t const game_title_start_w;
	extern uint16_t const game_title_start_h;
	extern uint16_t const heart [7 * 6];
	extern bool const heart_alpha [7 * 6];
	extern uint16_t const heart_w;
	extern uint16_t const heart_h;
	extern uint16_t const level1 [20 * 20];
	extern bool const level1_alpha [20 * 20];
	extern uint16_t const level1_w;
	extern uint16_t const level1_h;
	extern uint16_t const level2 [20 * 20];
	extern bool const level2_alpha [20 * 20];
	extern uint16_t const level2_w;
	extern uint16_t const level2_h;
	extern uint16_t const level3 [20 * 20];
	extern bool const level3_alpha [20 * 20];
	extern uint16_t const level3_w;
	extern uint16_t const level3_h;
	extern uint16_t const nine [7 * 8];
	extern bool const nine_alpha [7 * 8];
	extern uint16_t const nine_w;
	extern uint16_t const nine_h;
	extern uint16_t const one [7 * 8];
	extern bool const one_alpha [7 * 8];
	extern uint16_t const one_w;
	extern uint16_t const one_h;
	extern uint16_t const player [8 * 8];
	extern bool const player_alpha [8 * 8];
	extern uint16_t const player_w;
	extern uint16_t const player_h;
	extern uint16_t const player_bullet_1 [3 * 3];
	extern bool const player_bullet_1_alpha [3 * 3];
	extern uint16_t const player_bullet_1_w;
	extern uint16_t const player_bullet_1_h;
	extern uint16_t const player_bullet_2 [4 * 4];
	extern bool const player_bullet_2_alpha [4 * 4];
	extern uint16_t const player_bullet_2_w;
	extern uint16_t const player_bullet_2_h;
	extern uint16_t const player_bullet_3 [5 * 5];
	extern bool const player_bullet_3_alpha [5 * 5];
	extern uint16_t const player_bullet_3_w;
	extern uint16_t const player_bullet_3_h;
	extern uint16_t const rare_sword [8 * 8];
	extern bool const rare_sword_alpha [8 * 8];
	extern uint16_t const rare_sword_w;
	extern uint16_t const rare_sword_h;
	extern uint16_t const seven [7 * 8];
	extern bool const seven_alpha [7 * 8];
	extern uint16_t const seven_w;
	extern uint16_t const seven_h;
	extern uint16_t const six [7 * 8];
	extern bool const six_alpha [7 * 8];
	extern uint16_t const six_w;
	extern uint16_t const six_h;
	extern uint16_t const star [9 * 9];
	extern bool const star_alpha [9 * 9];
	extern uint16_t const star_w;
	extern uint16_t const star_h;
	extern uint16_t const sword [8 * 8];
	extern bool const sword_alpha [8 * 8];
	extern uint16_t const sword_w;
	extern uint16_t const sword_h;
	extern uint16_t const three [7 * 8];
	extern bool const three_alpha [7 * 8];
	extern uint16_t const three_w;
	extern uint16_t const three_h;
	extern uint16_t const two [7 * 8];
	extern bool const two_alpha [7 * 8];
	extern uint16_t const two_w;
	extern uint16_t const two_h;
	extern uint16_t const wall_1 [8 * 8];
	extern bool const wall_1_alpha [8 * 8];
	extern uint16_t const wall_1_w;
	extern uint16_t const wall_1_h;
	extern uint16_t const wall_2 [8 * 8];
	extern bool const wall_2_alpha [8 * 8];
	extern uint16_t const wall_2_w;
	extern uint16_t const wall_2_h;
	extern uint16_t const wall_3 [8 * 8];
	extern bool const wall_3_alpha [8 * 8];
	extern uint16_t const wall_3_w;
	extern uint16_t const wall_3_h;
	extern uint16_t const zero [7 * 8];
	extern bool const zero_alpha [7 * 8];
	extern uint16_t const zero_w;
	extern uint16_t const zero_h;

}

#endif