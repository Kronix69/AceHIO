#include "vector3.h"
#include <functions/functions.h>

namespace ace
{
	namespace engine
	{
		vector3::vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;

		}

		vector3::vector3()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		vector3 vector3::operator*(float value)
		{
			return vector3(this->x * value, this->y * value, this->z * value);
		}

		vector3 vector3::operator*(vector3 value)
		{
			return vector3(this->x * value.x, this->y * value.y, this->z * value.y);
		}

		vector3 vector3::back = vector3(0, 0, -1);
		vector3 vector3::down = vector3(0, -1, 0);
		vector3 vector3::forward = vector3(0, 0, 1);
		vector3 vector3::left = vector3(-1, 0, 0);
		vector3 vector3::one = vector3(1, 1, 1);
		vector3 vector3::right = vector3(1, 0, 0);
		vector3 vector3::up = vector3(0, 1, 0);
		vector3 vector3::zero = vector3(0, 0, 0);
	}
}