#include "playercontroller.h"
#include <memdata/memdata.h>
#include <functions/functions.h>
#include <iostream>
#include <controllers/userservicecontroller/userservicecontroller.h>
#include <unityengine/list/list.h>
#include <unityengine/transform/transform.h>

std::vector<ace::controller::player> players = {};

namespace ace
{
	namespace controller
	{
		bool player::assert_player()
		{
			if (this->address == 0)
			{
				throw "Invalid Player!";
				return false;
			}

			return true;
		}

		std::uintptr_t player::get_address()
		{
			if (!assert_player()) return 0;

			return this->address;
		}

		void player::set_hole_score(int hole, int score)
		{
			if (!assert_player()) return;

			ace::functions::user::set_hole_score(this->address, hole, score);
		}
		int player::get_hole_score(int hole)
		{
			if (!assert_player()) return 0;

			return ace::functions::user::get_hole_score(this->address, hole);
		}

		std::string player::get_display_name()
		{
			if (!assert_player()) return "";

			return ace::functions::user::get_display_name(this->address);
		}

		void player::set_spin_force(float spin)
		{
			if (!assert_player()) return;
			*reinterpret_cast<float*>(this->address + 0x98) = spin;
			return ace::functions::user::set_spin_force(this->address, spin);
		}

		ballmovement player::get_ball()
		{
			if (!assert_player()) return 0;

			auto ball = ace::functions::user::get_ball(this->address);

			if (!ball)
			{
				throw "Player does not have a ball assigned yet!";
				return ballmovement(0x0);
			}

			return ballmovement(ball);
		}


		void player::set_ball(ballmovement ball_movement)
		{
			if (!assert_player()) return;

			return ace::functions::user::set_ball(this->address, ball_movement.get_address());
		}

		void player::replace_ball(const std::string& name)
		{
			auto plr = ace::controller::user_service.get_player_by_name(name);
			auto ball_movement = plr.get_ball();

			this->ball_movement = ballmovement(this->get_ball());
			this->set_ball(ball_movement);
			this->bm_user = plr.get_address();

			*reinterpret_cast<std::uintptr_t*>(ball_movement.get_address() + 16) = this->address;
		}

		void player::restore_ball()
		{
			auto ball_movement = this->get_ball();
			*reinterpret_cast<std::uintptr_t*>(ball_movement.get_address() + 16) = this->bm_user;

			this->set_ball(this->ball_movement.get_address());
			this->ball_movement = ballmovement(0x0);
		}

		void player::set_ball_position(vector3& position)
		{
			auto ball_movement = this->get_ball();

			ball_movement.set_position(position);
		}

		vector3 player::get_flag_position(int hole)
		{
			auto camera_follow = *reinterpret_cast<std::uintptr_t*>(this->address + ace::memdata::user::camera_follow);

			auto flags_list = engine::list(*reinterpret_cast<std::uintptr_t*>(camera_follow + 176));

			auto vector = flags_list.get_vector();

			for (std::uintptr_t flag : vector)
			{
				auto hole_num = *reinterpret_cast<int*>(flag + 24);

				if (hole_num == hole)
					return engine::transform(*reinterpret_cast<std::uintptr_t*>(flag + 32)).get_position();
			}

			throw "Could not find a flag for specified hole!";


			/*auto flags = *reinterpret_cast<std::uintptr_t*>(flags_list + 16);

			auto flags_size = *reinterpret_cast<int*>(flags_list + 24);

			for (std::size_t i = 0; i < flags_size; i++)
			{
				auto flag = *reinterpret_cast<std::uintptr_t*>(flags + 0x20 + i * 8);

				auto hole_num = *reinterpret_cast<int*>(flag + 24);

				if (hole_num == hole)
					return engine::transform(*reinterpret_cast<std::uintptr_t*>(flag + 32)).get_position();
			}*/
		}

		vector3 player::get_camera_angle()
		{
			auto camera_follow = *reinterpret_cast<std::uintptr_t*>(this->address + ace::memdata::user::camera_follow);

			auto getfunction = reinterpret_cast<std::uintptr_t(__fastcall*)(const char*)>(0x1F7950 + ace::memdata::game_base);

			//auto gettransform = reinterpret_cast<std::uintptr_t(__fastcall*)(std::uintptr_t)>(*reinterpret_cast<std::uintptr_t*>(0x27F2F98 + ace::memdata::game_base));

			auto gettransform = reinterpret_cast<std::uintptr_t(__fastcall*)(std::uintptr_t)>(getfunction("UnityEngine.Component::get_transform()"));

			auto transform = engine::transform(gettransform(camera_follow));

			if (!transform.get_address())
				throw "Transform is not set!";

			auto vector = transform.get_eulerangles();

			return vector;
		}
	}
}