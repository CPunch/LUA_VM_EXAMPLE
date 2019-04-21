// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

extern void _start();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		AllocConsole();
		FILE* cons;
		freopen_s(&cons, "conin$", "r", stdin);
		freopen_s(&cons, "conout$", "w", stdout);
		SetConsoleTitle(L"LUA CONSOLE");
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)_start, NULL, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

