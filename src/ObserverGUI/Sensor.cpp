#include "Sensor.h"
#include <chrono>


void Sensor::setPosition(Status status)
{
	status_ = status;
	signal_(status);
}

Sensor::Sensor()
{
}

Sensor::~Sensor()
{
}

