#pragma once
#include "ballmovement/ballmovement.h"
#include <cstdint>
#include <vector>
#include <string>

namespace ace
{
	namespace controller
	{
		class player
		{
		protected:
			std::uintptr_t address = 0x0;
			ballmovement ball_movement;
			std::uintptr_t bm_user = 0x0;
			bool assert_player();

		public:
			std::uintptr_t get_address();

			void set_hole_score(int hole, int score);
			int get_hole_score(int hole);

			ballmovement get_ball();
			void set_ball(ballmovement ball_movement);

			void set_ball_position(vector3& position);

			void set_spin_force(float spin);

			void replace_ball(const std::string& name);
			void restore_ball();

			std::string get_display_name();

			vector3 get_flag_position(int hole);

			vector3 get_camera_angle();

			player(std::uintptr_t ua) : address(ua) {}
		};
	}
}

extern std::vector<ace::controller::player> players;