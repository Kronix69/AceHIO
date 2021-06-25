#pragma once
#include <unityengine/transform/vector3/vector3.h>
#include <unityengine/rigidbody/rigidbody.h>
#include <cstdint>
#include <string>

using ace::engine::vector3;

namespace ace
{
	namespace controller
	{
		class ballmovement
		{
		protected:
			std::uintptr_t address = 0x0;
		public:
			std::uintptr_t get_address();
			vector3 get_position();
			void set_position(vector3& position);

			vector3 get_colliding_hole();
			std::string get_course_name();
			engine::rigidbody get_rigid_body();

			ballmovement(std::uintptr_t address) : address(address) {}
			ballmovement() {}
		};
	}
}