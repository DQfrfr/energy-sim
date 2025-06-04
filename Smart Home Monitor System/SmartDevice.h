#pragma once
#include "Device.h"
class SmartDevice : public Device
{
public:
	SmartDevice(DeviceType type, const std::string& name, short id, float limit) : Device(type, name, id)
	{
		powerLimit = limit;
		totalPowerUsed = 0;
	}
	SmartDevice(DeviceType type, const std::string& name, float consumption, short id, float limit) : Device(type, name, consumption, id)
	{
		powerLimit = limit;
		totalPowerUsed = 0;
	}
	SmartDevice(DeviceType type, const std::string& name, float consumption, short id, float limit, float powerUsed) : Device(type, name, consumption, id)
	{
		powerLimit = limit;
		totalPowerUsed = powerUsed;
	}

	float getPowerUsed() { return totalPowerUsed; }
	float getPowerLimit() { return powerLimit; }
	void setPowerUsed(float power) { totalPowerUsed = power; }
	void setLimit(float limit) { powerLimit = limit; }

	void update(float& totalPower) override;

private:
	float totalPowerUsed;
	float powerLimit;
};