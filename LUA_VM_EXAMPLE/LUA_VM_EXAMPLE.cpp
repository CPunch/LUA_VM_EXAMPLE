// LUA_VM_EXAMPLE.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Lua.h"
#include "Hooks.h"

C_Hook hook_gettop;
int lua_state = NULL;

int lua_gettop_hook(int l)
{
	hook_gettop.removeHook();

	lua_state = Lua::lua_newthread(l); // cache state
	Lua::lua_pop(l, 1); // clean stack

	std::cout << "captured state : " << lua_state << std::endl;
	return Lua::lua_gettop(l);
}

void _start()
{
	std::cout << "Lua VM Manipulation POC by CPunch\nRead here: https://openpunk.com/blog/3" << std::endl;
	std::cout << "Hooking lua_gettop and capturing lua state..." << std::endl;

	std::string input;

	hook_gettop.setSubs((void*)Lua::lua_gettop, (void*)lua_gettop_hook);
	hook_gettop.installHook();

	while (true)
	{
		// Get input
		std::cout << "> ";
		std::getline(std::cin, input);

		if (lua_state != NULL)
		{
			char* buffer = (char*)input.c_str();
			Lua::luaL_loadstring(lua_state, buffer);
			if (Lua::lua_pcall(lua_state, 0, 0, 0) != 0)
			{
				std::cout << "ERROR: " << Lua::lua_tostring(lua_state, -1) << std::endl;
			}
			lua_state = Lua::lua_newthread(lua_state);
		}
	}
}
