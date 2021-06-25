#include "list.h"

namespace ace
{
	namespace engine
	{
			std::vector<std::uintptr_t> list::get_vector()
			{
				std::vector<std::uintptr_t> result;

				auto list = this->address;

				auto arr = *reinterpret_cast<std::uintptr_t*>(list + 16);
				auto len = *reinterpret_cast<int*>(list + 24);

				for (std::size_t i = 0; i < len; i++)
				{
					auto element = *reinterpret_cast<std::uintptr_t*>(arr + 0x20 + i * sizeof std::uintptr_t);
					result.push_back(element);
				}

				return result;
			}
	}
}
