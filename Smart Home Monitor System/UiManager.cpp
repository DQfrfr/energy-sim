#include "UiManager.h"
#include "StringUtil.h"

/* Displays main menu and returns int value based off user's choice. Should never 
return any value other than 1-7. A return of -1 indicates an error in input or an invalid choice. */
int UiManager::displayMainMenu()
{
	int choice;
	std::cout << "[1] View All Devices" << std::endl;
	std::cout << "[2] Toggle Devices On/Off" << std::endl;
	std::cout << "[3] Add New Device" << std::endl;
	std::cout << "[4] Remove Device" << std::endl;
	std::cout << "[5] Run Sim" << std::endl;
	std::cout << "[6] Reset Energy Usage Counter" << std::endl;
	std::cout << "[7] Clear Terminal" << std::endl;
	std::cout << "[8] Delete Devices.txt File" << std::endl;
	std::cout << "[9] Exit" << std::endl;

	std::cin >> choice;
	if (std::cin.fail())
	{
		std::cin.clear(); // Clear the error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
		return -1; // Return an error code
	}

	if (choice < 1 || choice > 9)
	{
		std::cout << "Invalid choice. Please try again." << std::endl;
		return -1; // Return an error code
	}
	std::cout << std::endl;
	return choice; // Return the valid choice
}

void UiManager::displayDevices(std::vector<Device*>& devices)
{
	if (devices.empty())
	{
		std::cout << "No devices found." << std::endl;
		return;
	}

	for (Device* device : devices) {
		std::cout << (*device);
	}
	std::cout << std::endl;
}

int UiManager::toggleDeviceState(std::vector<Device*>& devices)
{
	if (devices.empty())
	{
		std::cout << "No devices found." << std::endl;
		return -1; // Return an error code
	}

	int counter = 1;
	std::cout << "[0] Toggle All" << std::endl;
	for (Device* device : devices)
	{
		std::cout << "[" << counter << "] " << device->getDeviceName() << " - ";
		if (device->isOn())
		{
			std::cout << "On" << std::endl;
		} 
		else 
		{
			std::cout << "Off" << std::endl;
		}
		counter++;
	}
	
	int choice;
	while (1)
	{
		std::cout << "Please choose a device to turn on/off (-1) to exit" << std::endl;
		std::cin >> choice;
		if (choice == -1)
		{
			std::cout << std::endl;
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
		std::cout << std::endl;
		return choice;
	}
}

//[0] = type of device, [1] = device name, [2] = device category, [3] = if it exist, its either user inputed power draw or Smart device power limit, [4] = if exist its smart device power limit
std::vector<std::string> UiManager::collectDeviceDetails()
{
	std::vector<std::string> deviceDetails;
	std::string deviceType;
	std::string name;
	std::string type;
	float wattHours;

	while (1)
	{
		short type;
		std::cout << "Would you like to add a 1. Device, 2. Smart Device, 3. Battery Powered Device" << std::endl;
		std::cin >> type;
		if (std::cin.fail())
		{
			std::cout << "Please enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (type < 1 || type > 3)
		{
			std::cout << "Please enter a valid option. 1, 2, or 3" << std::endl;
			continue;
		}
		deviceDetails.push_back(std::to_string(type));
		break;
	}

	while (1)
	{
		std::cout << "Please enter the devices name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
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
		type = StringUtil::toLower(type); // Convert to lowercase for consistency

		if (type == "d")
		{
			displayAllApplianceTypes();
			continue;
		}
		deviceDetails.push_back(type);
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

	if (deviceDetails.at(0) == "2")
	{
		float drawLimit;
		while (1)
		{
			std::cout << "Please enter devices Power draw limit" << std::endl;
			std::cin >> drawLimit;
			if (std::cin.fail())
			{
				std::cout << "Please enter a number" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			if (drawLimit <= 0)
			{
				std::cout << "Power draw must be greater than 0" << std::endl;
				continue;
			}
			deviceDetails.push_back(std::to_string(drawLimit));
			break;
		}
	}

	return deviceDetails;
}

void UiManager::displayAllApplianceTypes()
{
	std::cout << std::endl;
	Device device;

	for (int i = 1; i <= static_cast<int>(DeviceType::COUNT) - 1; i++)
	{
		device.changeType(static_cast<DeviceType>(i));
		std::cout << "[" << i << "] " << device.getDeviceType() << std::endl;
	}

	std::cout << std::endl;
}