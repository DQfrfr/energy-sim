#include "SmartDevice.h"

void SmartDevice::update(float& tot)
{
	if (totalPowerUsed >= powerLimit)
	{
		std::cout << "Device has reached its power limit. Shutting off!" << std::endl;
		flipPowerState();
		return;
	}
	std::cout << "Device ID: " << getDeviceID() << std::endl;
	std::cout << "Device Name: " << getDeviceName() << std::endl;
	std::cout << "Device Type: " << getDeviceType() << std::endl;
	std::cout << "Power Consumption Left: " << powerLimit - totalPowerUsed << " W" << std::endl;
	std::cout << "------------------------" << std::endl;
	float consumption = (getPowerConsumption() / 3600) * 5;
	totalPowerUsed += consumption;
	tot += consumption;
}
