#pragma once
#include"Sensor.h"
class HaveSensors
{
public:
	/**
		Constructor
		Creates Sensors for each .xml file in ./sensors
	*/
	HaveSensors();
	~HaveSensors();
	/**
		update sensor readings
	*/
	void sensorsUpdate(double x, double y);
private:

	boost::filesystem::path sensorPath = boost::filesystem::path(".\\sensors");
	std::list<Sensor*> readings;
public:
	std::list<std::pair<double,double>> getReadings();
};

