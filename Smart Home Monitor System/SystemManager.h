#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "Device.h"
#include "UiManager.h"

class SystemManager
{
public:
	void start();

	SystemManager()
	{
		// Initialize the UI manager and devices
		uiManager = UiManager();
		totalPowerConsumption = 0.0f;
		devices = std::vector<Device*>();
	}

private:
	UiManager uiManager;
	std::vector<Device*> devices;
	float totalPowerConsumption;

	void runSim();
	void toggleDeviceState();
	void addDevice();
	void removeDevice()
	{
		std::cout << "Remove device functionality not implemented yet." << std::endl;
	}
	DeviceType stringToDeviceType(std::string& deviceType);
};

