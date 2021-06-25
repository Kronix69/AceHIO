#include "funchook.h"
#include <cstdint>
#include <minhook/minhook.h>
#include <memdata/memdata.h>
#include <iostream>
#include <controllers/playercontroller/playercontroller.h>
#include <controllers/userservicecontroller/userservicecontroller.h>
#include <main/main.h>

#define USER_HOOK true

using class_onupdate = std::uintptr_t(__fastcall*)(std::uintptr_t);

class_onupdate userservice_onupdate_backup = nullptr;

bool handler_on = false;

std::uintptr_t __fastcall userservice_onupdate_detour(std::uintptr_t usersv)
{
	auto ret = userservice_onupdate_backup(usersv);

	if (movement)
		movement_handler();
	
	if (commands.size())
	{
		command_handler(commands.front());
		commands.pop_front();
	}

	return ret;
}

bool mininit = false;

bool hook_functions()
{
	if (MH_Initialize() != MH_OK)
		return false;

#if USER_HOOK
	if (MH_CreateHook(reinterpret_cast<LPVOID>(ace::memdata::userservice::on_update), &userservice_onupdate_detour,
		              reinterpret_cast<LPVOID*>(&userservice_onupdate_backup)) != MH_OK)
		return false;

	if (MH_EnableHook(reinterpret_cast<LPVOID>(ace::memdata::userservice::on_update)) != MH_OK)
		return false;
#endif

	return true;
}