#include "UiManager.h"

/* Displays main menu and returns int value based off user's choice. Should never 
return any value other than 1-7. A return of -1 indicates an error in input or an invalid choice. */
int UiManager::displayMainMenu()
{
	int choice;
	std::cout << "[1] View All Devices" << std::endl;
	std::cout << "[2] Toggle Devices On/Off" << std::endl;
	std::cout << "[3] Add New Device" << std::endl;
	std::cout << "[4] Remove Device" << std::endl;
	std::cout << "[5] View Current Energy Usage (since last reset)" << std::endl;
	std::cout << "[6] Reset Energy Usage Counter" << std::endl;
	std::cout << "[7] Exit" << std::endl;

	std::cin >> choice;
	if (std::cin.fail())
	{
		std::cin.clear(); // Clear the error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
		return -1; // Return an error code
	}

	if (choice < 1 || choice > 7)
	{
		std::cout << "Invalid choice. Please try again." << std::endl;
		return -1; // Return an error code
	}
	return choice; // Return the valid choice
}

void UiManager::displayDevices(std::vector<Device*>& devices)
{
	for (Device* device : devices) {
		std::cout << "Device ID: " << device->getDeviceID() << std::endl;
		std::cout << "Device Name: " << device->getDeviceName() << std::endl;
		std::cout << "Device Type: " << device->getDeviceType() << std::endl;
		std::cout << "Power Consumption: " << device->getPowerConsumption() << " W" << std::endl;
		std::cout << "------------------------" << std::endl;
	}
}

int UiManager::toggleDeviceState(std::vector<Device*>& devices)
{
	int counter = 1;
	for (Device* device : devices)
	{
		std::cout << "[" << counter << "] " << device->getDeviceName() << " - ";
		if (device->isOnOff())
		{
			std::cout << "On" << std::endl;
		} 
		else 
		{
			std::cout << "Off" << std::endl;
		}
	}
	
	int choice;
	while (1)
	{
		std::cout << "Please choose a device to turn on/off (-1) to exit" << std::endl;
		std::cin >> choice;
		if (choice == -1)
		{
			return -1;
		}
		else if (choice < 0)
		{
			std::cout << "Please enter a positive value" << std::endl;
			continue;
		}
		else if (choice > counter)
		{
			std::cout << "Please enter a valid option" << std::endl;
			continue;
		}
		return choice;
	}
}

std::vector<std::string> UiManager::collectDeviceDetails()
{
	std::vector<std::string> deviceDetails;
	std::string name;
	std::string type;
	float wattHours;

	while (1)
	{
		std::cout << "Please enter the devices name" << std::endl;
		std::cin >> name;
		if (name.size() <= 1)
		{
			std::cout << "Name must be longer than 1 charachter" << std::endl;
			continue;
		}
		deviceDetails.push_back(name);
		break;
	}

	//TODO: add in functionality to display all types
	while (1)
	{
		std::cout << "Please enter the Device catergory (Type 'D' to display types)" << std::endl;
		std::cin >> type;
		if (type.size() < 2)
		{
			std::cout << "Device category should be longer than 2 charachters" << std::endl;
			continue;
		}
		break;
	}

	while (1)
	{
		std::cout << "Please enter applicance energy consumption (Kwh). -1 to skip" << std::endl;
		std::cin >> wattHours;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (wattHours == -1)
		{
			break;
		}
		else if (wattHours < 0) {
			std::cout << "Wattage cannot be negative" << std::endl;
			continue;
		}
		else if (wattHours > 4500) {
			wattHours = 4500;
		}
		deviceDetails.push_back(std::to_string(wattHours));
		break;
	}

	return deviceDetails;
}
