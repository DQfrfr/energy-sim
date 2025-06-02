#include "SystemManager.h"
#include <memory>

int main()
{
	std::unique_ptr<SystemManager> sys = std::make_unique<SystemManager>();
	return 0;
}