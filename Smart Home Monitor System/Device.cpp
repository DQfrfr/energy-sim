#include "Device.h"

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
	case DeviceType::Light: return "Light";
	case DeviceType::Fridge: return "Fridge";
	case DeviceType::TV: return "TV";
	case DeviceType::Heater: return "Heater";
	case DeviceType::AirConditioner: return "Air Conditioner";
	case DeviceType::Fan: return "Fan";
	case DeviceType::Washer: return "Washer";
	case DeviceType::Dryer: return "Dryer";
	case DeviceType::Oven: return "Oven";
	case DeviceType::Microwave: return "Microwave";
	case DeviceType::Computer: return "Computer";
	case DeviceType::Router: return "Router";
	case DeviceType::Charger: return "Charger";
	case DeviceType::Speaker: return "Speaker";
	default: return "Custom";
	}
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
