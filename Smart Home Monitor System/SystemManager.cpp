#include "SystemManager.h"
#include "StringUtil.h"
#include <unordered_map>
#include <cstdlib> 
#include <memory>
#include <cstdio>
#include <iomanip>

void SystemManager::start()
{
	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator on startup
	//devices.push_back(new Device(DeviceType::AirConditioner, "test", generateID())); // put here purley to make passing off easier
	//devices.push_back(new SmartDevice(DeviceType::Computer, "test2", generateID(), 1));
	//devices.push_back(new BatteryDevice(DeviceType::Dryer, "test3", generateID(), 0));
	loadDevices();

	while (1)
	{
		switch (uiManager.displayMainMenu())
		{
		case 1:
			uiManager.displayDevices(devices);
			continue;
		case 2:
			toggleDeviceState();
			continue;
		case 3:
			addDevice();
			system("cls");
			continue;
		case 4:
			removeDevice();
			continue;
		case 5:
			runSim();
			continue;
		case 6:
			system("cls");
			std::cout << "Resetting energy usage counter..." << std::endl;
			totalPowerConsumption = 0.0f; // Reset the total power consumption
			continue;
		case 7:
			system("cls"); // Clear the terminal
			continue;
		case 8:
			if (std::remove("Devices.txt") == 0) {
				std::cout << "File deleted successfully." << std::endl;
			}
			else {
				std::cout << "Error deleting file";
			}
			continue;
		case 9:
			std::cout << "Exiting the system. Goodbye!" << std::endl;
			saveDevices();
			for (Device* device : devices) {
				delete device; // Clean up dynamically allocated devices
				device = nullptr;
			}
			devices.clear();
			return;
		}
	}
}

short SystemManager::generateID()
{
	short num = rand() % 1000;
	if (usedIds.empty())
	{
		usedIds.push_back(num);
		return num;
	}

	while (1)
	{
		for (int id : usedIds)
		{
			if (id == num)
			{
				num = rand() % 1000; // Generate a new random number
				break; // Break out of the for loop to check the new number
			}
		}
		return num; // If no match found, return the unique ID
	}
}

//TODO - allow user to set the simulation time, and the time between each device check
void SystemManager::runSim()
{
	// here to control runtime
	float runtimeLimMin = .08;

	// Edge Cases
	if (devices.empty())
	{
		std::cout << "No devices!" << std::endl;
		return;
	}
	else if (!hasActiveDevices())
	{
		std::cout << "No active devices found. Exiting simulation." << std::endl;
		return; // Exit if no active devices
	}

	int runtime = 0;
	while (1)
	{
		for (Device* device : devices) {
			if (!device->isOn())
			{
				continue; // Skip devices that are off
			}
			device->update(totalPowerConsumption);
		}
		std::cout << "Total Power Consumption: " << totalPowerConsumption << " W" << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		runtime += 5; // Increment runtime by 5 seconds
		if (runtime >= (60.0f * runtimeLimMin)) // If runtime reaches specified runtime
		{
			system("cls");
			std::cout << "Simulation has run for " << runtime << " seconds. Exiting..." << std::endl;
			std::cout << "Total Power Consumption: " << totalPowerConsumption << " W" << std::endl;
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

void SystemManager::addDevice()
{
	//[0] = type of device, [1] = device name, [2] = device category
	//[3] = if it exist, its either user inputed power draw or Smart device power limit, [4] = if exist its smart device power limit

	std::vector<std::string> deviceDetails = uiManager.collectDeviceDetails();
	DeviceType deviceType = stringToDeviceType(deviceDetails[2]);
	std::string name = deviceDetails.at(1);

	if (deviceDetails.size() == 4)
	{
		float powerConsumption = std::stof(deviceDetails[3]);
		switch (std::stoi(deviceDetails.at(0)))
		{
		case 1:
			devices.push_back(new Device(deviceType, name, powerConsumption, generateID()));
			return;
		case 2:
			devices.push_back(new SmartDevice(deviceType, name, generateID(), powerConsumption));
			return;
		case 3:
			devices.push_back(new BatteryDevice(deviceType, name, powerConsumption, generateID()));
			return;
		}
	}
	else if (deviceDetails.size() == 5)
	{
		float powerConsumption = std::stof(deviceDetails[3]);
		float powerLimit = std::stof(deviceDetails[4]);
		devices.push_back(new SmartDevice(deviceType, name, powerConsumption, generateID(), powerLimit));
	}

	switch (std::stoi(deviceDetails.at(0)))
	{
	case 1:
		devices.push_back(new Device(deviceType, name, generateID()));
		return;
	case 3:
		devices.push_back(new BatteryDevice(deviceType, name, generateID()));
		return;
	}
}
 
void SystemManager::removeDevice()
{
	if (devices.empty())
	{
		std::cout << "No devices to remove." << std::endl;
		return;
	}

	int deviceID;
	uiManager.displayDevices(devices);
	std::cout << "Please enter the ID of the device you want to delete (-1 to delete all)" << std::endl;
	while (1)
	{
		std::cin >> deviceID;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
			std::cout << "Invalid input. Please enter a valid device ID." << std::endl;
			continue;
		}
		break;
	}

	if (deviceID == -1)
	{
		for(Device* d : devices)
		{
			delete d;
		}
		devices.clear();
		std::cout << "All devices deleted!" << std::endl;
		return;
	}

	system("cls"); // clear terminal to keep everything clear
	int count = 0;
	for (Device* device : devices)
	{
		if (*(device) == deviceID)
		{
			std::cout << "Removing device: " << (*device).getDeviceName() << std::endl;
			delete device; // Free the memory allocated for the device
			devices.erase(devices.begin() + count);
			return;
		}
		count++;
	}
	std::cout << "Device with ID " << deviceID << " not found." << std::endl;
}

bool SystemManager::hasActiveDevices()
{
	if (devices.empty())
	{
		return false; // No devices at all
	}

	for (Device* device : devices)
	{
		if (device->isOn())
		{
			return true; // At least one device is active
		}
	}
	return false; // No active devices found
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

void SystemManager::saveDevices()
{
	std::ofstream save("Devices.txt");
	if (!save.good())
	{
		std::cout << "Loading failed." << std::endl;
		save.close();
		return;
	}

	for (Device* device : devices)
	{
		if (BatteryDevice* bd = dynamic_cast<BatteryDevice*>(device))
		{
			save << "3" << " " << static_cast<int>(bd->getType()) << " " << std::quoted(bd->getDeviceName()) << " " << bd->getPowerConsumption() << " " << bd->getBatteryLevel() << '\n';
		}
		else if (SmartDevice* sd = dynamic_cast<SmartDevice*>(device))
		{
			save << "2" << " " << static_cast<int>(sd->getType()) << " " << std::quoted(sd->getDeviceName()) << " " << sd->getPowerConsumption() << " " << sd->getPowerLimit() << " " << sd->getPowerUsed() << '\n';
		}
		else
		{
			save << "1" << " " << static_cast<int>(device->getType()) << " " << std::quoted(device->getDeviceName()) << " " << device->getPowerConsumption() << '\n';
		}
	}
	save.close();
}

void SystemManager::loadDevices()
{
	std::ifstream load("Devices.txt");
	if (!load.good())
	{
		load.close();
		return;
	}

	int type;
	int cat;
	float consumption;
	std::string name;
	
	while (load >> type >> cat >> std::quoted(name) >> consumption)
	{
		DeviceType devType = static_cast<DeviceType>(cat);
		switch (type)
		{
		case 1:
			devices.push_back(new Device(devType, name, consumption, generateID()));
			break;
		case 2:
			float limit;
			float used;
			load >> limit >> used;
			devices.push_back(new SmartDevice(devType, name, consumption, generateID(), limit, used));
			break;
		case 3:
			int battery;
			load >> battery;
			devices.push_back(new BatteryDevice(devType, name, consumption, generateID(), battery));
			break;
		}
	}
	load.close();
}
