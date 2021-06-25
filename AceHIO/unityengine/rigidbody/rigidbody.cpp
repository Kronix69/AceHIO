#include "rigidbody.h"
#include <functions/functions.h>

namespace ace
{
	namespace engine
	{
		void rigidbody::add_force(const vector3& force)
		{
			ace::functions::rigidbody::add_force(this->address, force);
		}

		void rigidbody::add_force(const vector3& force, force_mode mode)
		{
			ace::functions::rigidbody::add_force(this->address, force, mode);
		}
	}
}