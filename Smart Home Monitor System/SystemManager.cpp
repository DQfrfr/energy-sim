#include "SystemManager.h"
#include "StringUtil.h"
#include <unordered_map>
#include <cstdlib> 

void SystemManager::start()
{
	while (1)
	{
		switch (uiManager.displayMainMenu())
		{
		case 1:
			uiManager.displayDevices(devices);
			break;
		case 2:
			toggleDeviceState();
			break;
		case 3:
			addDevice();
			system("cls");
			break;
		case 4:
			removeDevice();
			system("cls");
			break;
		case 5:
			runSim();
			system("cls");
			std::cout << "Total Power Consumption: " << totalPowerConsumption << " W" << std::endl;
			break;
		case 6:
			system("cls");
			std::cout << "Resetting energy usage counter..." << std::endl;
			totalPowerConsumption = 0.0f; // Reset the total power consumption
			break;
		case 7:
			std::cout << "Exiting the system. Goodbye!" << std::endl;
			for (Device* device : devices) {
				delete device; // Clean up dynamically allocated devices
			}
			exit(0); // Exit the loop and end the program
		}
	}
}

//Todo make this run on its own thread, and pick up where it left off if the user exits the simulation
void SystemManager::runSim()
{
	if (devices.empty())
	{
		std::cout << "No devices!";
		return;
	}
	int runtime = 0;
	while (1)
	{
		for (Device* device : devices) {
			std::cout << "Device ID: " << device->getDeviceID() << std::endl;
			std::cout << "Device Name: " << device->getDeviceName() << std::endl;
			std::cout << "Device Type: " << device->getDeviceType() << std::endl;
			std::cout << "Power Consumption: " << device->getPowerConsumption() << " W" << std::endl;
			std::cout << "------------------------" << std::endl;
			totalPowerConsumption += (device->getPowerConsumption() / 3600) * 5;
		}
		std::cout << "Total Power Consumption: " << totalPowerConsumption << " W" << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		runtime += 5; // Increment runtime by 5 seconds
		if (runtime >= 60) // If runtime reaches 60 seconds
		{
			std::cout << "Simulation has run for 60 seconds. Exiting..." << std::endl;
			return; // Exit the simulation loop
		}

	}
}

void SystemManager::toggleDeviceState()
{
	int choice = uiManager.toggleDeviceState(devices);
	if (choice == -1)
	{
		return;
	}
	else if (choice == 0) // Toggle all devices
	{
		for (Device* device : devices)
		{
			device->flipPowerState();
		}
		return;
	}
	else if (choice < 1 || choice > devices.size())
	{
		std::cout << "Invalid choice. Please try again." << std::endl;
		return;
	}

	devices[choice - 1]->flipPowerState();
}

//TODO possibly allow user to enter number of Enum values when creating an appliance.
void SystemManager::addDevice()
{
	std::vector<std::string> deviceDetails = uiManager.collectDeviceDetails();
	DeviceType deviceType = stringToDeviceType(deviceDetails[1]);
	if (deviceDetails.size() == 3)
	{
		float powerConsumption = std::stof(deviceDetails[2]);
		devices.push_back(new Device(deviceType, deviceDetails[0], powerConsumption));
		return;
	}
	devices.push_back(new Device(deviceType, deviceDetails[0]));
	std::cout << std::endl;
}

DeviceType SystemManager::stringToDeviceType(std::string& type)  
{  
	std::unordered_map<std::string, DeviceType> deviceTypeMap = {
		{"light", DeviceType::Light},
		{"fridge", DeviceType::Fridge},
		{"tv", DeviceType::TV},
		{"heater", DeviceType::Heater},
		{"air conditioner", DeviceType::AirConditioner},
		{"fan", DeviceType::Fan},
		{"washer", DeviceType::Washer},
		{"dryer", DeviceType::Dryer},
		{"oven", DeviceType::Oven},
		{"microwave", DeviceType::Microwave},
		{"computer", DeviceType::Computer},
		{"router", DeviceType::Router},
		{"charger", DeviceType::Charger},
		{"speaker", DeviceType::Speaker},
		{"1", DeviceType::Light },
		{"2", DeviceType::Fridge},
		{"3", DeviceType::TV},
		{"4", DeviceType::Heater},
		{"5", DeviceType::AirConditioner},
		{"6", DeviceType::Fan},
		{"7", DeviceType::Washer},
		{"8", DeviceType::Dryer},
		{"9", DeviceType::Oven},
		{"10", DeviceType::Microwave},
		{"11", DeviceType::Computer},
		{"12", DeviceType::Router},
		{"13", DeviceType::Charger},
		{"14", DeviceType::Speaker}
	};

	for (auto& pair : deviceTypeMap) {
		if (StringUtil::toLower(type) == pair.first) {
			return pair.second;
		}
	}
	return DeviceType::Custom; // Return Custom if no match found
}
