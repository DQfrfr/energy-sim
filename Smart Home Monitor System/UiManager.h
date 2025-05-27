#pragma once
#include <iostream>
#include "Device.h"
#include <vector>

class UiManager
{
public:
	int displayMainMenu();
	void displayDevices(std::vector<Device*>& devices);
	int toggleDeviceState(std::vector<Device*>& devices);
	std::vector<std::string> collectDeviceDetails();
	void displayAllApplianceTypes();

};

