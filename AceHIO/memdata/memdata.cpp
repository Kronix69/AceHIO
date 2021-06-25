#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstddef>

namespace ace
{
	namespace memdata
	{
		std::uintptr_t game_base = 0x0;

		namespace user
		{
			std::ptrdiff_t camera_follow;

			std::uintptr_t constructor;
			std::uintptr_t set_hole_score;
			std::uintptr_t get_hole_score;

			std::uintptr_t get_in_hole;
			std::uintptr_t set_in_hole;

			std::uintptr_t get_ball;
			std::uintptr_t set_ball;

			std::uintptr_t set_spin_force;

			std::uintptr_t get_display_name;
		}

		namespace userservice
		{
			std::ptrdiff_t users_list;

			std::uintptr_t get;
			std::uintptr_t constructor;
			std::uintptr_t get_users;
			std::uintptr_t remove_user;

			std::uintptr_t on_update;
		}

		namespace ballmovement
		{
			std::ptrdiff_t colliding_hole;
			std::ptrdiff_t course_name;
			std::ptrdiff_t rigid_body;

			std::uintptr_t set_position;
		}

		namespace transform
		{
			std::uintptr_t get_position;
			std::uintptr_t set_position;

			std::uintptr_t get_eulerangles;
		}

		namespace rigid_body
		{
			std::uintptr_t add_force;
			std::uintptr_t add_mode_force;
		}

		namespace game
		{
			std::uintptr_t get_hole_number;
			std::uintptr_t get_hole_spawn;
		}

		bool ready_addresses()
		{
			while (!game_base)
				game_base = reinterpret_cast<std::uintptr_t>(GetModuleHandle("GameAssembly.dll"));

			/* Offsets */

			user::camera_follow = 72;

			userservice::users_list = 16;

			ballmovement::colliding_hole = 136;
			ballmovement::course_name = 1088;
			ballmovement::rigid_body = 696;


			/* Addresses */

			user::constructor = 0x325200 + game_base;
			user::set_hole_score = 0x324020 + game_base;
			user::get_hole_score = 0x323FE0 + game_base;

			user::get_in_hole = 0x323E40 + game_base;
			user::set_in_hole = 0x323E50 + game_base;


			user::get_ball = 0x323070 + game_base;
			user::set_ball = 0x323280 + game_base;

			user::set_spin_force = 0x3242D0 + game_base;

			user::get_display_name = 0x322F10 + game_base;

			userservice::get = 0x29C290 + game_base;
			userservice::constructor = 0x328D30 + game_base;
			userservice::get_users = 0x328230 + game_base;
			userservice::remove_user = 0x327DD0 + game_base;

			userservice::on_update = 0x327940 + game_base;

			ballmovement::set_position = 0x3F8EB0 + game_base;;

			transform::get_position = 0x1532640 + game_base;
			transform::set_position = 0x15326C0 + game_base;

			transform::get_eulerangles = 0x1532800 + game_base;

			rigid_body::add_force = 0x1B65340 + game_base;
			rigid_body::add_mode_force = 0x1B652D0 + game_base;

			game::get_hole_number = 0x3EE9B0 + game_base;
			game::get_hole_spawn = 0x3F9FA0 + game_base;

			return true;
		}
	}

}