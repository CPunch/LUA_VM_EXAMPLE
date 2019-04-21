#include "stdafx.h"
#include "Lua.h"

TluaL_loadbuffer Lua::luaL_loadbuffer = (TluaL_loadbuffer)(BASE(ADDR_LOADBUFFER));
Tlua_pcall Lua::lua_pcall = (Tlua_pcall)(BASE(ADDR_PCALL));
Tlua_gettop Lua::lua_gettop = (Tlua_gettop)(BASE(ADDR_GETTOP));
Tlua_settop Lua::lua_settop = (Tlua_settop)(BASE(ADDR_SETTOP));
Tlua_newthread Lua::lua_newthread = (Tlua_newthread)(BASE(ADDR_NEWTHREAD));
Tlua_tolstring Lua::lua_tolstring = (Tlua_tolstring)(BASE(ADDR_TOLSTRING));