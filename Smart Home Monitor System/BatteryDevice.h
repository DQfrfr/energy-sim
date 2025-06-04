#pragma once
#include "Device.h"
class BatteryDevice : public Device
{
public:
	BatteryDevice(DeviceType type, const std::string& name, short id) : Device(type, name, id)
	{
		batteryPercentage = 100;
	}
	BatteryDevice(DeviceType type, const std::string& name, float consumption, short id) : Device(type, name, consumption, id)
	{
		batteryPercentage = 100;
	}

	//Temporary constructor to make passing off easier;
	BatteryDevice(DeviceType type, const std::string& name, float consumption, short id, int battery) : Device(type, name, consumption, id)
	{
		batteryPercentage = battery;
	}

	int getBatteryLevel() { return batteryPercentage; }

	void flipPowerState() override;

	void update(float& totalPower) override;

private:
	int batteryPercentage;

};

