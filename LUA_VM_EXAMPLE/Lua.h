#pragma once

#define ADDR_LOADBUFFER 0x0081C070
#define ADDR_PCALL 0x0081B220
#define ADDR_GETTOP 0x0081A4A0
#define ADDR_SETTOP 0x0081A4B0
#define ADDR_NEWTHREAD 0x0081B790
#define ADDR_TOLSTRING 0x0081A8A0
#define BASE(ADDR) (ADDR - 0x00400000) + (DWORD)GetModuleHandle(NULL)

// MACROS
#define lua_tostring(l, i) lua_tolstring(l, i, NULL)
#define lua_pop(l, i) lua_settop(l, -(i)-1)
#define luaL_loadstring(L, s) luaL_loadbuffer(L, s, strlen(s), s)

typedef int(__cdecl *TluaL_loadbuffer)(int lua_state, char* buffer, size_t size, char* chunkname);
typedef int(__cdecl *Tlua_pcall)(int lua_state, int a, int b, int c);
typedef int(__cdecl *Tlua_gettop)(int lua_state);
typedef int(__cdecl *Tlua_settop)(int lua_state, int a);
typedef int(__cdecl *Tlua_newthread)(int lua_state);
typedef char*(__cdecl *Tlua_tolstring)(int lua_state, int a, size_t* b);

namespace Lua
{
	extern TluaL_loadbuffer luaL_loadbuffer;
	extern Tlua_pcall lua_pcall;
	extern Tlua_gettop lua_gettop;
	extern Tlua_settop lua_settop;
	extern Tlua_newthread lua_newthread;
	extern Tlua_tolstring lua_tolstring;
}