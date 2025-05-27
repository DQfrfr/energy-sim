#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "Device.h"
#include "UiManager.h"
#include "SystemManager.h"

int main()
{
	SystemManager systemManager;
	systemManager.start();
	return 0;
}
