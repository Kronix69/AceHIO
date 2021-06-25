#pragma once
#include <cstdint>
#include <cstddef>

namespace ace
{
	namespace engine
	{

		struct vector3
		{
			//std::uint32_t padding[4];
			float x;
			float y;
			float z;

			vector3 operator*(float value);
			vector3 operator*(vector3 value);

			static vector3 back;
			static vector3 down;
			static vector3 forward;
			static vector3 left;
			static vector3 one;
			static vector3 right;
			static vector3 up;
			static vector3 zero;

			vector3(float x, float y, float z);
			vector3();
		};
	}
}

