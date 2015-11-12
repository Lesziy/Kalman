#include "Trajectory.h"



Trajectory::Trajectory() : time(0)
{
}


Trajectory::~Trajectory()
{
}

void Trajectory::SetDestination(std::function<void(Status)> fn)
{
	receiver = fn;
}

void Trajectory::RunTo(double x, double y)
{
	receiver(Status(x, y));
	time++;
}
