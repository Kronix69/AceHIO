#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <controllers/playercontroller/playercontroller.h>
#include <controllers/userservicecontroller/userservicecontroller.h>

extern std::deque<std::string> commands;


extern bool movement;

void movement_handler();
void command_handler(std::string);