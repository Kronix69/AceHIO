#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstddef>

namespace ace
{
	namespace memdata
	{
		extern std::uintptr_t game_base;

		namespace user
		{
			extern std::ptrdiff_t camera_follow;

			extern std::uintptr_t constructor;
			extern std::uintptr_t set_hole_score;
			extern std::uintptr_t get_hole_score;

			extern std::uintptr_t get_in_hole;
			extern std::uintptr_t set_in_hole;

			extern std::uintptr_t get_ball;
			extern std::uintptr_t set_ball;

			extern std::uintptr_t set_spin_force;

			extern std::uintptr_t get_display_name;
		}

		namespace userservice
		{
			extern std::ptrdiff_t users_list;

			extern std::uintptr_t get;
			extern std::uintptr_t constructor;
			extern std::uintptr_t get_users;
			extern std::uintptr_t remove_user;

			extern std::uintptr_t on_update;
		}

		namespace timer
		{
			extern std::uintptr_t update;
		}

		namespace ballmovement
		{
			extern std::ptrdiff_t colliding_hole;
			extern std::ptrdiff_t course_name;
			extern std::ptrdiff_t rigid_body;

			extern std::uintptr_t set_position;
		}

		namespace transform
		{
			extern std::uintptr_t get_position;
			extern std::uintptr_t set_position;

			extern std::uintptr_t get_eulerangles;
		}

		namespace rigid_body
		{
			extern std::uintptr_t add_force;
			extern std::uintptr_t add_mode_force;
		}

		namespace game
		{
			extern std::uintptr_t get_hole_number;
			extern std::uintptr_t get_hole_spawn;
		}

		bool ready_addresses();
	}

}