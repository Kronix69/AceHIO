#pragma once
#include "vector3/vector3.h"

namespace ace
{
	namespace engine
	{
		class transform
		{
		protected:
			std::uintptr_t address;
		public:
			std::uintptr_t get_address();
			vector3 get_position();
			void set_position(vector3* p);
			vector3 get_eulerangles();
			
			transform(std::uintptr_t address) : address(address) {}
		};
	}
}

