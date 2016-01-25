#include "SensorWorker.h"
#include <ctime>


SensorWorker::SensorWorker(const std::pair<double, double>& noiseXY_)
{
	srand(time(0));
	noiseXY = noiseXY;
}


SensorWorker::~SensorWorker()
{
}

Status SensorWorker::ThreadProc(Status s) {
	s.type = SENSORS;

	s.x = s.x + fRand(-noiseXY.first, noiseXY.first);
	s.y = s.y + fRand(-noiseXY.second, noiseXY.second);

	return s;
}

double SensorWorker::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}