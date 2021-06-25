#pragma once
#include <vector>

namespace ace
{
	namespace engine
	{
		class list
		{
		protected:
			std::uintptr_t address = 0x0;

		public:
			std::vector<std::uintptr_t> get_vector();

			list(std::uintptr_t address) : address(address) {}
		};
	}
}

