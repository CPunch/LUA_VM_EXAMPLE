#pragma once
#include "QPatch.h"


/************************************************
	CLASS NAME:
		CANNED Hook
	AUTHOR:
		CPunch
	DESCRIPTION:
		Custom hooking library for x86 processes.
*************************************************/

// macros (mostly opcode stuff for intel/AMD processors)
#define JMP_OPCODE 0xE9
#define RTN_OPCODE 0xC3
#define JMP_BUFFER 6

// class
class C_Hook
{
private:
	void * originalsub; // holds address of original sub
	void * newsub; // holds address of the sub we will jmp too
	QPatch* jpatch; // holds original bytes, jmp bytes, and memory page protection
	bool installed;
public:
	C_Hook(); // default constructor to create object
	C_Hook(void * osub, void * nsub); // constructor to create object
	void setSubs(void * osub, void * nsub);
	// hook related modifiers
	bool installHook();
	bool removeHook();
};
