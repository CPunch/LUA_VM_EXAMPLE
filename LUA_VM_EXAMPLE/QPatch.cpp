#include "stdafx.h"
#include "QPatch.h"

QPatch::QPatch(void * ad, BYTE* n_bytes, size_t sz)
{
	addr = ad;
	size = sz;
	new_bytes = new BYTE[sz];
	orig_bytes = new BYTE[sz];

	if (VirtualProtect(n_bytes, sz, PAGE_EXECUTE_READWRITE, &oldproc) == 0)
	{
		std::cout << "VMP FAILED !!" << std::endl;
		return;
	}
	memcpy(new_bytes, n_bytes, sz);
	VirtualProtect(n_bytes, sz, oldproc, &oldproc);

}

bool QPatch::patch()
{
	if (VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &oldproc) == 0)
	{
		return false;
	}

	// save bytes and replace
	memcpy(orig_bytes, addr, size);
	memcpy(addr, new_bytes, size);

	return true;
}

bool QPatch::unpatch()
{
	// replace patched bytes with original
	memcpy(addr, orig_bytes, size);

	// return 
	if (VirtualProtect(addr, size, oldproc, &oldproc) == 0)
	{
		return false;
	}

	return true;
}
