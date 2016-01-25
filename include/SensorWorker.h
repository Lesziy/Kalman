#pragma once
#include "Common.h"

class SensorWorker : public Worker<CommonUtil::InputOutputWorker>
{
public:
	SensorWorker(const std::pair<double, double>& noiseXY_);
	~SensorWorker();

	Status ThreadProc(Status s);

	private:
		std::pair<double, double> noiseXY;
		double fRand(double fMin, double fMax);
};

