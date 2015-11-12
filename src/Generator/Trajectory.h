#pragma once
#include <functional>
#include "Status.h"
class Trajectory
{
	unsigned int time;
	static std::function<void(Status)> receiver;

public:
	Trajectory();
	~Trajectory();

	static void SetDestination(std::function<void(Status)> fn);
	
	void RunTo(double x, double y);
};

