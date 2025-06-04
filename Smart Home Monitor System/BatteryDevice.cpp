#include "BatteryDevice.h"

void BatteryDevice::flipPowerState()
{
	if (batteryPercentage <= 0 && !isOn())
	{
		std::cout << "Changing Batteries" << std::endl;
		batteryPercentage = 100;
		isActive = true;
		return;
	}
	if (isActive)
	{
		isActive = false;
	}
	else
	{
		isActive = true;
	}
}

void BatteryDevice::update(float& tot)
{
	if (batteryPercentage != 0)
	{
		batteryPercentage -= 2;
	}
	if (batteryPercentage <= 0)
	{
		std::cout << "Device has ran out of battery. Shutting off!" << std::endl;
		flipPowerState();
		batteryPercentage = 0;
		return;
	}
	std::cout << "Device ID: " << getDeviceID() << std::endl;
	std::cout << "Device Name: " << getDeviceName() << std::endl;
	std::cout << "Device Type: " << getDeviceType() << std::endl;
	std::cout << "Battery Left: " << batteryPercentage << "%" << std::endl;
	std::cout << "------------------------" << std::endl;
	tot += (getPowerConsumption() / 3600) * 5;
}
