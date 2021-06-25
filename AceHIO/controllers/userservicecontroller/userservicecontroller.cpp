#include "userservicecontroller.h"
#include <unityengine/list/list.h>
#include <functions/functions.h>
#include <iostream>

namespace ace
{
	namespace controller
	{
		userservice user_service(0x0);

		bool userservice::assert_service()
		{
			if (this->address == 0)
			{
				throw "Invalid Service!\n";
			}
		}

		std::vector<player> userservice::get_players()
		{
			std::vector<player> players = {};

			assert_service();

			auto playerlist = ace::functions::userservice::get_users(this->address).get_vector();

			for (std::uintptr_t ptr : playerlist)
				players.push_back(player(ptr));

			return players;
		}

		player userservice::get_local_player()
		{
			assert_service();

			auto players = get_players();

			return players.size() ? get_players().at(0) : player(0x0);
		}

		player userservice::get_player(std::uint64_t index)
		{
			assert_service();

			auto players = get_players();

			return index - 1 < players.size() ? get_players().at(index - 1) : get_local_player();
		}

		player userservice::get_player_by_name(const std::string& name)
		{
			assert_service();

			auto players = get_players();

			for (player plr : players)
			{
				auto plrname = plr.get_display_name();

				if (plrname.length() >= name.length() && plrname.substr(0, name.length()) == name)
				{
					return plr;
				}
			}

			throw std::string("Failed to get " + name).c_str();

			return player(0x0);
		}

		void userservice::remove_player(const std::string& name)
		{
			assert_service();

			auto player = this->get_player_by_name(name);

			ace::functions::userservice::remove_user(this->address, player.get_address());
		}
	}
}