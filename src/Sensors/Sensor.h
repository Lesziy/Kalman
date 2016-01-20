#pragma once
#include <boost/filesystem.hpp>
class Sensor
{
public:
	Sensor(boost::filesystem::path);
	void updateCoordinates(double x, double y);
	std::pair<double, double> getCooridnates();
private:
	double noise;
	std::pair<double, double> outCoordinates;
};

