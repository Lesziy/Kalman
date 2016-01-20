#include "Sensor.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


Sensor::Sensor(boost::filesystem::path path)
{
	boost::property_tree::ptree data;
	boost::property_tree::read_xml(path.string(), data);
	noise = data.get<double>("sensor.noise");
	outCoordinates = std::pair<double, double>();
}

void Sensor::updateCoordinates(double x, double y)
{
	outCoordinates = std::pair<double, double>(x*noise, y*noise);
}

std::pair<double, double> Sensor::getCooridnates()
{
	return outCoordinates;
}
