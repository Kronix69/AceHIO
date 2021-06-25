#include "transform.h"
#include <functions/functions.h>
#include <iostream>

namespace ace
{
	namespace engine
	{
		std::uintptr_t transform::get_address()
		{
			return this->address;
		}

		vector3 transform::get_position()
		{
			vector3 result;

			ace::functions::transform::get_position(result, this->address);

			return result;
		}

		void transform::set_position(vector3* p)
		{
			ace::functions::transform::set_position(*p, this->address);
		}

		vector3 transform::get_eulerangles()
		{
			vector3 result;

			ace::functions::transform::get_eulerangles(result, this->address);

			return result;
		}

	}
}