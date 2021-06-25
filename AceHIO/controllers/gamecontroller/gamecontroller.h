#pragma once
#include <unityengine/transform/vector3/vector3.h>

using ace::engine::vector3;

namespace ace
{
	namespace controller
	{
		class game
		{
		public:
			int get_hole_number();
			vector3 get_hole_spawn(int hole);

			game() {}
		};

		extern game game_manager;
	}
}