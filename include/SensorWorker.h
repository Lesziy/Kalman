#pragma once
#include "Common.h"

using namespace CommonUtil;

class SensorWorker : public Worker<Traits::InputOutputWorker>
{
public:
	SensorWorker(const std::pair<double, double>& noiseXY_);
	~SensorWorker();

	Status ThreadProc(Status s);

	private:
		std::pair<double, double> noiseXY;
		double fRand(double fMin, double fMax);
};

