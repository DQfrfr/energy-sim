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
		// Initialize the UI manager and devices and starts program
		uiManager = UiManager();
		totalPowerConsumption = 0.0f;
		devices = std::vector<Device*>();
		start();
	}

private:
	UiManager uiManager;
	std::vector<int> usedIds;
	std::vector<Device*> devices;
	float totalPowerConsumption;
	short generateID();
	void runSim();
	void toggleDeviceState();
	void addDevice();
	void removeDevice();
	bool hasActiveDevices();
	DeviceType stringToDeviceType(std::string& deviceType);
};

