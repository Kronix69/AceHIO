#pragma once
#include <cstdint>
#include <vector>
#include <controllers/playercontroller/playercontroller.h>

namespace ace
{
	namespace controller
	{
		class userservice
		{
		protected:
			std::uintptr_t address = 0x0;
			bool assert_service();
		public:
			std::vector<player> get_players();

			player get_local_player();
			void remove_player(const std::string&);
			player get_player(std::uint64_t player);
			player get_player_by_name(const std::string&);

			userservice(std::uintptr_t addy) : address(addy) {}
		};
		extern userservice user_service;
	}
}