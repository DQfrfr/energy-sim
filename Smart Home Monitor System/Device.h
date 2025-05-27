#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <random>

enum class DeviceType {
	Light = 1,             // 60 W - average value
	Fridge = 2,            // 150 W - average value
	TV = 3,                // 100 W - average value
	Heater = 4,            // 1500 W - average value
	AirConditioner = 5,    // 2000 W - average value
	Fan = 6,               // 75 W - average value
	Washer = 7,            // 500 W - average value
	Dryer = 8,             // 3000 W - average value
	Oven = 9,              // 2400 W - average value
	Microwave = 10,        // 1100 W - average value
	Computer = 11,         // 250 W - average value
	Router = 12,           // 10 W - average value
	Charger = 13,          // 5 W - average value
	Speaker = 14,          // 20 W - average value
	Custom = 15,            // (user-defined)
	COUNT // Total number of device types
};


class Device
{
public:
	void printDeviceTyoes()
	{
		
	}

	short getDeviceID() {
		return deviceID;
	}

	std::string getDeviceName() {
		return deviceName;
	}

	void flipPowerState();

	bool isOnOff() { return isActive; }

	void setDeviceName(std::string& name) {
		if (name.empty()) {
			std::cerr << "Device name cannot be empty." << std::endl;
			return;
		}
		deviceName = name;
	}

	std::string getDeviceType();

	void changeType(DeviceType type);

	float getPowerConsumption() {
		return powerConsumption;
	}

	void setPowerConsumption(float consumption);

	Device() {}

	Device(DeviceType type, const std::string& name)
	{
		deviceName = name;
		deviceType = static_cast<DeviceType> (type);
		isActive = false; // Default to inactive
		setPowerConsumption();
	}

	Device(DeviceType type, const std::string& name, float consumption)
	{
		deviceName = name;
		deviceType = static_cast<DeviceType> (type);
		isActive = false; // Default to inactive
		setPowerConsumption(consumption);
	}

private:
	//TODO: Device ID needs to be unique across all devices
	const short deviceID = rand() % 10000 + 1; // Random ID between 1 and 10000
	std::string deviceName;
	DeviceType deviceType;
	float powerConsumption; // in watts
	bool isActive;

	void setPowerConsumption();
};