#include "gamecontroller.h"
#include <functions/functions.h>

namespace ace
{
	namespace controller
	{
		game game_manager;

		int game::get_hole_number()
		{
			return ace::functions::game::get_hole_number() - 1;
		}

		vector3 game::get_hole_spawn(int hole)
		{
			return ace::functions::game::get_hole_spawn(hole + 1).get_position();
		}
	}
}