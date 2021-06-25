// dllmain.cpp : Defines the entry point for the DLL application.
#include "main.h"
#include <Windows.h>
#include <funchook/funchook.h>
#include <vector>
#include <memdata/memdata.h>
#include <functions/functions.h>
#include <sstream>
#include <controllers/gamecontroller/gamecontroller.h>
#include <math.h>

std::deque<std::string> commands;

DWORD WINAPI Start(LPVOID)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);

    std::cout << " -- Welcome to AceHIO (Hole In One) --\n";
    try
    {
        std::cout << "Initialising memory!\n";
        ace::memdata::ready_addresses();
        ace::functions::ready_functions();

        if (!hook_functions())
            throw "FATAL ERROR: Failed to hook functions!";
        auto userservice_addy = ace::functions::userservice::get();
        ace::controller::user_service = ace::controller::userservice(userservice_addy);

        std::cout << std::hex << "Base: " << ace::memdata::game_base << "\n";
        std::cout << std::hex << "User Service: " << userservice_addy << "\n";

        std::string cmd;

        for (;;)
        {
            std::getline(std::cin, cmd);

            if (cmd.empty())
                continue;

            commands.push_back(cmd);
        }
    }
    catch (const char* error)
    {
        std::cout << error << "\n";
    }
    return 1;
}

std::vector<std::string> split_string(std::string str)
{
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return vstrings;
}

bool movement = false;

float control_speed = 0.25;

constexpr float deg2rad(float degrees)
{
    double pi = 3.14159265359;

    return (degrees / 180.00) * pi;
}

void movement_handler()
{
    auto localplayer = ace::controller::user_service.get_player(1);
    auto cameraangle = localplayer.get_camera_angle().y;

    bool up = GetKeyState(VK_UP) & 0x8000;
    bool right = GetKeyState(VK_RIGHT) & 0x8000;
    bool down = GetKeyState(VK_DOWN) & 0x8000;
    bool left = GetKeyState(VK_LEFT) & 0x8000;

    bool jump = GetKeyState(VK_SPACE) & 0x8000;

    vector3 movement;
    float speed = control_speed;

    auto cosval = cos(deg2rad(cameraangle));
    auto sinval = sin(deg2rad(cameraangle));

    auto forward = speed * sinval;
    auto sideways = speed * cosval;

   

    if (up || down)
    {
        float inc = up ? 1.00 : -1.00;
        movement.x = forward * inc;
        movement.z = sideways * inc;
    }
    if (right || left)
    {
        float inc = right ? 1.00 : -1.00;
        if (abs(sideways) < abs(forward))
        {
            movement.x = -sideways * inc;
            movement.z = -forward * inc;
        }
        else
        {
            movement.x = sideways * inc;
            movement.z = forward * inc;
        }
    }
    //movement.x = up ? speed : movement.x;
   // movement.x = down ? -speed : movement.x;

    movement.y = jump ? 2 : 0;

  //  movement.z = left ? speed : movement.z;
  //  movement.z = right ? -speed : movement.z;

   // movement = movement * *localplayer.get_camera_position();

    localplayer.get_ball().get_rigid_body().add_force(movement, ace::engine::force_mode::velocitychange);
}

auto lastpos = vector3(0, 0, 0);

void command_handler(std::string cmd)
{
    auto tokens = split_string(cmd);

    if (!tokens.size())
        return;

    auto command = tokens[0];

    try
    {
        if (command == "getplayers")
        {
            auto players = ace::controller::user_service.get_players();
            for (ace::controller::player player : players)
                std::cout << "name: " << player.get_display_name() << "\n";
        }
        else if (command == "currentpos")
        {
            auto ballpos = ace::controller::user_service.get_local_player().get_ball().get_position();

            std::cout << "ballpos: " << std::dec << ballpos.x << " " << ballpos.y << " " << ballpos.z << "\n";
            std::cout << "diff: " << std::dec << ballpos.x - lastpos.x << " " << ballpos.y - lastpos.y << " " << ballpos.z - lastpos.z<< "\n";

            lastpos = ballpos;
        }
        else if (command == "camerapos")
        {
            auto camerapos = ace::controller::user_service.get_player(1).get_camera_angle();

            std::cout << "camerapos: " << std::dec << camerapos.x << " " << camerapos.y << " " << camerapos.z << "\n";
        }
        else if (command == "setcontrolspeed")
        {
            if (tokens.size() < 2)
                throw "Invalid number of arguments to command (1)";

            auto speed = tokens[1];

            control_speed = atof(speed.c_str());
        }
        else if (command == "control")
        {
            if (tokens.size() < 2)
                throw "Invalid number of arguments to command (1)";

            auto mode = tokens[1];

            if (mode == "on")
                movement = true;
            else if (mode == "off")
                movement = false;
        }
        else if (command == "radius")
        {
            std::cout << "ball radius: " << *reinterpret_cast<float*>(ace::controller::user_service.get_local_player().get_ball().get_address() + 444) << "\n";
        }
        else if (command == "force")
        {
            if (tokens.size() < 3)
                throw "Invalid number of arguments to command (2)";

            auto player_name = tokens[1];

            auto force = atoi(tokens[2].c_str());

            auto vec = vector3(force,0,0);

            ace::controller::user_service.get_player_by_name(player_name).get_ball().get_rigid_body().add_force(vec, ace::engine::force_mode::velocitychange);
        }
        else if (command == "force2")
        {
            if (tokens.size() < 2)
                throw "Invalid number of arguments to command (1)";

            auto player_name = tokens[1];

            auto vec = vector3(14.0849440973, 0, 0);

            ace::controller::user_service.get_player_by_name(player_name).get_ball().get_rigid_body().add_force(vec, ace::engine::force_mode::velocitychange);
        }
        else if (command == "teleport")
        {
            if (tokens.size() < 3)
                throw "Invalid number of arguments to command (2)";     

            auto player_name = tokens[1];
            auto argument = tokens[2];

            if (argument == "spawn")
            {
                auto position = ace::controller::game_manager.get_hole_spawn(ace::controller::game_manager.get_hole_number());

                std::cout << "position: " << position.x << " " << position.y << " " << position.z << "\n";

                ace::controller::user_service.get_player_by_name(player_name).set_ball_position(position);
            }
            else if (argument == "hole")
            {
                auto player = ace::controller::user_service.get_player_by_name(player_name);
                auto position = player.get_flag_position(ace::controller::game_manager.get_hole_number() + 1);

                std::cout << "position: " << position.x << " " << position.y << " " << position.z << "\n";

                player.set_ball_position(position);
            }
        }
        else if (command == "coursename")
        {
            std::cout << "course name: " << ace::controller::user_service.get_player(1).get_ball().get_course_name() << "\n";
        }
        else if (command == "currenthole")
        {
            std::cout << "hole number: " << ace::controller::game_manager.get_hole_number() << "\n";
        }
        else if (command == "replaceball")
        {
            if (tokens.size() < 3)
            {
                throw "Invalid number of arguments to command (2)";
                return;
            }

            auto name = tokens[1];
            auto name2 = tokens[2];

            ace::controller::user_service.get_player_by_name(name).replace_ball(name2);
        }
        else if (command == "restoreball")
        {
            if (tokens.size() < 2)
            {
                throw "Invalid number of arguments to command (1)";
                return;
            }

            auto name = tokens[1];

            ace::controller::user_service.get_player_by_name(name).restore_ball();
        }
        else if (command == "remove")
        {
            if (tokens.size() < 2)
            {
                throw "Invalid number of arguments to command (1)";
                return;
            }

            auto name = tokens[1];

            ace::controller::user_service.remove_player(name);
        }
        else if (command == "setscore")
        {
            if (tokens.size() < 4)
            {
                throw "Invalid number of arguments to command (3)";
                return;
            }

            auto name = tokens[1];
            auto hole = atoi(tokens[2].c_str()), score = atoi(tokens[3].c_str());

            ace::controller::user_service.get_player_by_name(name).set_hole_score(hole, score);
        }
        else if (command == "getscore")
        {
            if (tokens.size() < 3)
            {
                throw "Invalid number of arguments to command (2)";
                return;
            }

            auto name = tokens[1];
            auto hole = atoi(tokens[2].c_str());

            std::cout << "Score is: " << ace::controller::user_service.get_player_by_name(name).get_hole_score(hole) << "\n";
        }
        else if (command == "setspin")
        {
            if (tokens.size() < 3)
            {
                throw "Invalid number of arguments to command (2)";
                return;
            }

            auto name = tokens[1];
            auto spin = atoi(tokens[2].c_str());

            ace::controller::user_service.get_player_by_name(name).set_spin_force(spin);
        }
        else
        {
            throw "Unrecognised command!";
        }
    }
    catch (const char* msg)
    {
        std::cout << "Command error: " << msg << "\n";
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, Start, 0, 0, 0);
        break;
    }
    return TRUE;
}

