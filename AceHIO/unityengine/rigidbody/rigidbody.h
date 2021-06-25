#pragma once
#include <cstdint>
#include "../transform/vector3/vector3.h"

namespace ace
{
	namespace engine
	{
		enum class force_mode
		{
			force,
			velocitychange,
			impulse = 1,
			acceleration = 5
		};

		class rigidbody
		{
		protected:
			std::uintptr_t address;
		public:
			void add_force(const vector3&);
			void add_force(const vector3&, force_mode);

			rigidbody(std::uintptr_t address) : address(address) {}
		};
	}
}
