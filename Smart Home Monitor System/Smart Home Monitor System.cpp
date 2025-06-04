#define _CRT  DBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SystemManager.h"
#include <memory>

int main()
{
	// Smart pointer put in its own scope so the memory leak dump dosent detect it as a memory leak
	{
		std::unique_ptr<SystemManager> sys = std::make_unique<SystemManager>();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}