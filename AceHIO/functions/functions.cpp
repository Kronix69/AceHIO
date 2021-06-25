#include "functions.h"
#include <memdata/memdata.h>

namespace ace
{
	namespace functions
	{
		using getuserservice = std::uintptr_t(__cdecl*)();

		using setholescore = void(__fastcall*)(std::uintptr_t, int, int);
		using getholescore = int(__fastcall*)(std::uintptr_t, int);

		using setspinforce = void(__fastcall*)(std::uintptr_t, float);

		using getball = std::uintptr_t(__fastcall*)(std::uintptr_t);
		using setball = void(__fastcall*)(std::uintptr_t, std::uintptr_t);

		using getusers = std::uintptr_t(__fastcall*)(std::uintptr_t, int*);
		using removeuser = void(__fastcall*)(std::uintptr_t, std::uintptr_t);

		using getdisplayname = std::uintptr_t(__fastcall*)(std::uintptr_t);

		using bmsetposition = void(__fastcall*)(std::uintptr_t, vector3&);

		using transformposition = vector3* (__fastcall*)(vector3&, std::uintptr_t);

		using rbaddforce = void(__fastcall*)(std::uintptr_t, const vector3&);
		using rbaddmodeforce = void(__fastcall*)(std::uintptr_t, const vector3&, engine::force_mode);

		using getholenumber = int(__fastcall*)();
		using getholespawn = std::uintptr_t(__fastcall*)(std::uintptr_t, int);

		using geteulerangles = vector3 * (__fastcall*)(vector3&, std::uintptr_t);

		setholescore fset_hole_score;
		getholescore fget_hole_score;
		getdisplayname fget_display_name;
		setspinforce fset_spin_force;
		getball fget_ball;
		setball fset_ball;

		getusers fget_users;
		removeuser fremove_user;
		getuserservice fget_userservice;

		bmsetposition fbm_set_position;

		transformposition ftransformgetposition;
		transformposition ftransformsetposition;

		geteulerangles fgeteulerangles;

		rbaddforce frbaddforce;
		rbaddmodeforce frbaddmodeforce;

		getholenumber fget_hole_number;
		getholespawn fget_hole_spawn;

		std::string unistrtoansi(std::uintptr_t str)
		{
			if (*reinterpret_cast<int*>(str + 16))
			{
				auto ws = std::wstring(reinterpret_cast<wchar_t*>(str + 0x14));
				std::string s(ws.begin(), ws.end());

				return s;
			}
			else
				return "";
		}

		void ready_functions()
		{
			fset_hole_score = reinterpret_cast<setholescore>(ace::memdata::user::set_hole_score);
			fget_hole_score = reinterpret_cast<getholescore>(ace::memdata::user::get_hole_score);
			fget_ball = reinterpret_cast<getball>(ace::memdata::user::get_ball);
			fset_ball = reinterpret_cast<setball>(ace::memdata::user::set_ball);
			fget_display_name = reinterpret_cast<getdisplayname>(ace::memdata::user::get_display_name);
			fset_spin_force = reinterpret_cast<setspinforce>(ace::memdata::user::set_spin_force);

			fget_users = reinterpret_cast<getusers>(ace::memdata::userservice::get_users);
			fremove_user = reinterpret_cast<removeuser>(ace::memdata::userservice::remove_user);
			fget_userservice = reinterpret_cast<getuserservice>(ace::memdata::userservice::get);

			fbm_set_position = reinterpret_cast<bmsetposition>(ace::memdata::ballmovement::set_position);

			ftransformgetposition = reinterpret_cast<transformposition>(ace::memdata::transform::get_position);
			ftransformsetposition = reinterpret_cast<transformposition>(ace::memdata::transform::set_position);

			fgeteulerangles = reinterpret_cast<geteulerangles>(ace::memdata::transform::get_eulerangles);

			frbaddforce = reinterpret_cast<rbaddforce>(ace::memdata::rigid_body::add_force);
			frbaddmodeforce = reinterpret_cast<rbaddmodeforce>(ace::memdata::rigid_body::add_mode_force);

			fget_hole_number = reinterpret_cast<getholenumber>(ace::memdata::game::get_hole_number);
			fget_hole_spawn = reinterpret_cast<getholespawn>(ace::memdata::game::get_hole_spawn);
		}

		namespace user
		{

			void set_hole_score(std::uintptr_t user, int hole, int score)
			{
				fset_hole_score(user, hole, score);
			}

			int get_hole_score(std::uintptr_t user, int hole)
			{
				return fget_hole_score(user, hole);
			}

			void set_ball(std::uintptr_t user, std::uintptr_t ballmovement)
			{
				fset_ball(user, ballmovement);
			}

			std::uintptr_t get_ball(std::uintptr_t user)
			{
				return fget_ball(user);
			}

			std::string get_display_name(std::uintptr_t user)
			{
				return unistrtoansi(fget_display_name(user));
			}

			void set_spin_force(std::uintptr_t user, float spin)
			{
				fset_spin_force(user, spin);
			}
		}

		namespace userservice
		{
			std::uintptr_t get()
			{
				return fget_userservice();
			}

			engine::list get_users(std::uintptr_t userservice)
			{
				return engine::list(*reinterpret_cast<std::uintptr_t*>(userservice + ace::memdata::userservice::users_list));
			}
			
			void remove_user(std::uintptr_t userservice, std::uintptr_t user)
			{
				fremove_user(userservice, user);
			}
		}

		namespace ballmovement
		{
			engine::transform get_colliding_hole(std::uintptr_t ball_movement)
			{
				return engine::transform(*reinterpret_cast<std::uintptr_t*>(ball_movement + ace::memdata::ballmovement::colliding_hole));
			}

			std::string get_course_name(std::uintptr_t ball_movement)
			{
				auto strptr = *reinterpret_cast<std::uintptr_t*>(ball_movement + ace::memdata::ballmovement::course_name);

				if (!strptr)
					return "no course loaded";

				return unistrtoansi(strptr);
			}

			void set_position(std::uintptr_t ball_movement, vector3& position)
			{
				fbm_set_position(ball_movement, position);
			}
		}

		namespace transform
		{
			vector3* get_position(vector3& vector, std::uintptr_t transform)
			{
				return ftransformgetposition(vector, transform);
			}

			void set_position(vector3& vector, std::uintptr_t transform)
			{
				ftransformsetposition(vector, transform);
			}

			vector3* get_eulerangles(vector3& vector, std::uintptr_t transform)
			{
				return fgeteulerangles(vector, transform);
			}
		}

		namespace rigidbody
		{
			void add_force(std::uintptr_t rigidbody, const vector3& force)
			{
				frbaddforce(rigidbody, force);
			}

			void add_force(std::uintptr_t rigidbody, const vector3& force, engine::force_mode mode)
			{
				frbaddmodeforce(rigidbody, force, mode);
			}
		}

		namespace game
		{
			int get_hole_number()
			{
				return fget_hole_number();
			}

			engine::transform get_hole_spawn(int hole)
			{
				return engine::transform(fget_hole_spawn(0, hole));
			}
		}
	}
}