#include "HaveSensors.h"
#include <boost/filesystem.hpp>
#include<boost/regex.hpp>
#include <iostream>

HaveSensors::HaveSensors()
{
	boost::regex fileName{ "sensor\\d\\d\\.xml" };
	for (boost::filesystem::directory_iterator it(sensorPath);
	it != boost::filesystem::directory_iterator();
	 ++it)
	{
		if (boost::filesystem::is_regular_file(it->status()) && 
			boost::regex_match ( it->path().filename().string() , fileName) ) // if file in sensor directory is named as sensor definition
		{
			boost::filesystem::path pat= it->path();
			readings.push_back(new Sensor(pat));
		}
	}
}
HaveSensors::~HaveSensors()
{
	for (Sensor *s : readings)
	{
		delete s;
	}
}
void HaveSensors::sensorsUpdate(double x, double y)
{
	for (Sensor* s : readings)
	{
		s->updateCoordinates(x, y);
	}
}
std::list<std::pair<double, double>> HaveSensors::getReadings()
{
	std::list<std::pair<double, double>> returned;
	for (Sensor* s : readings)
	{
		returned.push_back(s->getCooridnates());
	}
	return returned;
}
