#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "Device.h"

int main()
{
	std::vector<Device> devices;

	std::string test = "Test Device Name";
	std::string test2 = "Test Device Name 2";
	std::string test3 = "Test Device Name 3";

	Device Device1(1, test);
	Device Device2(2, test2, 500.0f);
	Device Device3(3, test3, 100.0f);

	devices.push_back(Device1);
	devices.push_back(Device2);
	devices.push_back(Device3);
	float totalPowerConsumption = 0;

	while (1)
	{
		for (Device& device : devices) {
			std::cout << "Device ID: " << device.getDeviceID() << std::endl;
			std::cout << "Device Name: " << device.getDeviceName() << std::endl;
			std::cout << "Device Type: " << device.getDeviceType() << std::endl;
			std::cout << "Power Consumption: " << device.getPowerConsumption() << " W" << std::endl;
			std::cout << "------------------------" << std::endl;
			totalPowerConsumption += (device.getPowerConsumption() / 3600) * 5;
		}
		std::cout << "Press Ctrl+C to exit." << std::endl;
		std::cout << "Total Power Consumption: " << totalPowerConsumption << " W" << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		
	}
}
