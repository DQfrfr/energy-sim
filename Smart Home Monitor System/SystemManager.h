#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <chrono>
#include "Device.h"
#include "SmartDevice.h"
#include "BatteryDevice.h"
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
	void saveDevices();
	void loadDevices();
};

