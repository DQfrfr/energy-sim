#include "Device.h"

void Device::update(float& tot)
{
	std::cout << "Device ID: " << getDeviceID() << std::endl;
	std::cout << "Device Name: " << getDeviceName() << std::endl;
	std::cout << "Device Type: " << getDeviceType() << std::endl;
	std::cout << "Power Consumption: " << getPowerConsumption() << " W" << std::endl;
	std::cout << "------------------------" << std::endl;
	tot += (getPowerConsumption() / 3600) * 5;
}

void Device::flipPowerState()
{
	if (isActive)
	{
		isActive = false;
	} 
	else
	{
		isActive = true;
	}
}

std::string Device::getDeviceType()
{
	switch (deviceType) {
	case DeviceType::Light: return "Light (60W)";
	case DeviceType::Fridge: return "Fridge (150W)";
	case DeviceType::TV: return "TV (120W)";
	case DeviceType::Heater: return "Heater (1500W)";
	case DeviceType::AirConditioner: return "Air Conditioner (1000W)";
	case DeviceType::Fan: return "Fan (75W)";
	case DeviceType::Washer: return "Washer (500W)";
	case DeviceType::Dryer: return "Dryer (3000W)";
	case DeviceType::Oven: return "Oven (2400W)";
	case DeviceType::Microwave: return "Microwave (1100W)";
	case DeviceType::Computer: return "Computer (250W)";
	case DeviceType::Router: return "Router (10W)";
	case DeviceType::Charger: return "Charger (5W)";
	case DeviceType::Speaker: return "Speaker (50W)";
	default: return "Custom";
	}
}

void Device::changeType(DeviceType deviceType)
{
	this->deviceType = deviceType;
	setPowerConsumption();
}

void Device::setPowerConsumption()
{
	switch (deviceType) {
	case DeviceType::Light: powerConsumption = 60.0f; break;
	case DeviceType::Fridge: powerConsumption = 150.0f; break;
	case DeviceType::TV: powerConsumption = 100.0f; break;
	case DeviceType::Heater: powerConsumption = 1500.0f; break;
	case DeviceType::AirConditioner: powerConsumption = 2000.0f; break;
	case DeviceType::Fan: powerConsumption = 75.0f; break;
	case DeviceType::Washer: powerConsumption = 500.0f; break;
	case DeviceType::Dryer: powerConsumption = 3000.0f; break;
	case DeviceType::Oven: powerConsumption = 2400.0f; break;
	case DeviceType::Microwave: powerConsumption = 1100.0f; break;
	case DeviceType::Computer: powerConsumption = 250.0f; break;
	case DeviceType::Router: powerConsumption = 10.0f; break;
	case DeviceType::Charger: powerConsumption = 5.0f; break;
	case DeviceType::Speaker: powerConsumption = 20.0f; break;
	default: powerConsumption = 0.0f; // Custom or unknown device
	}
}

void Device::setPowerConsumption(float consumption)
{
	if (consumption <= 0) {
		std::cerr << "Power consumption must be greater than 0W." << std::endl;
		return;
	}
	else if (consumption > 4500) {
		std::cerr << "Power consumption cannot exceed 4500 W." << std::endl;
		return;
	}
	powerConsumption = consumption;
}

std::ostream& operator<<(std::ostream& os, Device dev)
{
	os << "Device ID: " << dev.getDeviceID() << std::endl;
	os << "Device Name: " << dev.getDeviceName() << std::endl;
	os << "Device Type: " << dev.getDeviceType() << std::endl;
	os << "Power Consumption: " << dev.getPowerConsumption() << " W" << std::endl;
	os << "State: " << (dev.isOn() ? "On" : "Off") << std::endl;
	os << "------------------------" << std::endl;
	return os;
}
