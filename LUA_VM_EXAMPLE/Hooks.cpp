#include "stdafx.h"
#include "Hooks.h"

// 0xE9 = JMP - jump to address
// 0xC3 = RTN - return to return address
// 0x90 = NOP - does nothing

BYTE tempJMP[JMP_BUFFER] = { JMP_OPCODE, 0x90, 0x90, 0x90, 0x90, RTN_OPCODE };

DWORD getrealitivedisplacement(DWORD from, DWORD to, DWORD insSize)
{
	if (to < from)
		return 0 - (from - to) - insSize;
	return to - (from + insSize);
}

// constructor
C_Hook::C_Hook()
{
	// default
	setSubs(0, 0);
}

// constructor
C_Hook::C_Hook(void * osub, void * nsub)
{
	setSubs(osub, nsub);
}

void C_Hook::setSubs(void * osub, void * nsub)
{
	originalsub = osub;
	newsub = nsub;

	// CREATE JMP PATCH
	BYTE jmpbytes[JMP_BUFFER];
	memcpy(jmpbytes, tempJMP, JMP_BUFFER); // copy original bytes to jmpbytes (for normal execution i guess)
	DWORD JMPSize = getrealitivedisplacement((DWORD)originalsub, (DWORD)newsub, 5); // get jmp distance
	memcpy(&jmpbytes[1], &JMPSize, 4); // write to our jmpbytes, now the instruction is ready to be written (DWORD = 4 BYTES)

	jpatch = new QPatch(originalsub, (BYTE*)jmpbytes, JMP_BUFFER);

	installed = false;
}

bool C_Hook::installHook()
{
	if (jpatch->patch())
	{
		installed = true;
		return true;
	}
	else
	{
		installed = false;
		return false;
	}
}

bool C_Hook::removeHook()
{
	if (jpatch->unpatch())
	{
		installed = false;
		return true;
	}
	else
	{
		return false;
	}
}
