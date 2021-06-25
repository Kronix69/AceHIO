#pragma once
#include <cstdint>
#include <string>
#include <unityengine/list/list.h>
#include <unityengine/transform/vector3/vector3.h>
#include <unityengine/transform/transform.h>
#include <unityengine/rigidbody/rigidbody.h>

using ace::engine::vector3;

namespace ace
{
	namespace functions
	{
		void ready_functions();

		namespace user
		{
			void set_hole_score(std::uintptr_t, int, int);
			int get_hole_score(std::uintptr_t, int);

			void set_ball(std::uintptr_t, std::uintptr_t);
			std::uintptr_t get_ball(std::uintptr_t);

			std::string get_display_name(std::uintptr_t);
			void set_spin_force(std::uintptr_t, float);
		}

		namespace userservice
		{
			std::uintptr_t get();
			engine::list get_users(std::uintptr_t userservice);
			void remove_user(std::uintptr_t, std::uintptr_t);
		}

		namespace ballmovement
		{
			engine::transform get_colliding_hole(std::uintptr_t);
			std::string get_course_name(std::uintptr_t);

			void set_position(std::uintptr_t ball_movement, vector3& position);
		}

		namespace transform
		{
			vector3* get_position(vector3&, std::uintptr_t);
			void set_position(vector3& , std::uintptr_t);

			vector3* get_eulerangles(vector3&, std::uintptr_t);
		}

		namespace rigidbody
		{
			void add_force(std::uintptr_t, const vector3&);
			void add_force(std::uintptr_t, const vector3&, engine::force_mode);
		}

		namespace game
		{
			int get_hole_number();
			engine::transform get_hole_spawn(int hole);
		}
	}
}
