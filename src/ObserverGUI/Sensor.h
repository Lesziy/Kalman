#pragma once
#include "Observee.h"
#include "Status.h"
class Sensor: public Observee
{
public:
	void setPosition(Status status);
	Sensor();
	~Sensor();
};

