#include "ballmovement.h"
#include <functions/functions.h>
#include <unityengine/transform/transform.h>
#include <memdata/memdata.h>

using ace::engine::transform;

namespace ace
{
	namespace controller
	{
		std::uintptr_t ballmovement::get_address()
		{
			return this->address;
		}

		vector3 ballmovement::get_position()
		{
			auto getfunction = reinterpret_cast<std::uintptr_t(__fastcall*)(const char*)>(0x1F7950 + ace::memdata::game_base);

			auto gettransform = reinterpret_cast<std::uintptr_t(__fastcall*)(std::uintptr_t)>(getfunction("UnityEngine.Component::get_transform()"));

			auto transform = engine::transform(gettransform(this->address));

			if (!transform.get_address())
				throw "Transform is not set!";

			auto vector = transform.get_position();

			return vector;
		}

		void ballmovement::set_position(vector3& position)
		{
			ace::functions::ballmovement::set_position(this->address, position);
		}

		vector3 ballmovement::get_colliding_hole()
		{
			auto colliding_hole = ace::functions::ballmovement::get_colliding_hole(this->address);
			
			if (!colliding_hole.get_address())
				throw "Could not get colliding hole!";
			
			return colliding_hole.get_position();
		}

		std::string ballmovement::get_course_name()
		{
			return ace::functions::ballmovement::get_course_name(this->address);
		}

		engine::rigidbody ballmovement::get_rigid_body()
		{
			return engine::rigidbody(*reinterpret_cast<std::uintptr_t*>(this->address + ace::memdata::ballmovement::rigid_body));
		}
	}
}