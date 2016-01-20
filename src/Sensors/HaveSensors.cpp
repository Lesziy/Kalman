#include "HaveSensors.h"
#include <boost/filesystem.hpp>
#include<boost/regex.hpp>
#include <iostream>

HaveSensors::HaveSensors()
{
	
	for (boost::filesystem::directory_iterator it(sensorPath);
	it != boost::filesystem::directory_iterator();
	 ++it)
	{
	}
}
void HaveSensors::sensorsUpdate(double x, double y)
{
	for (Sensor s : readings)
	{
		s.updateCoordinates(x, y);
	}
}
std::list<std::pair<double, double>> HaveSensors::getReadings()
{
	std::list<std::pair<double, double>> returned;
	for (Sensor s : readings)
	{
		returned.push_back(s.getCooridnates());
	}
	return returned;
}
