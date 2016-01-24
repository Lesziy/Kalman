#pragma once
#include <kalman/ekfilter.hpp>
#include <kalman/kfilter.hpp>

class KalmanFilter_1D : public Kalman::KFilter<double, 1, false, false, true>
{
public:
	KalmanFilter_1D(const double& time_step_, const double& pos_noise_, const double& acc_noise_);
	~KalmanFilter_1D();
	void initFilter(Vector& init_x);

protected:
	void makeBaseA();
	void makeBaseB();
	void makeBaseH();
	void makeBaseV();
	void makeBaseR();
	void makeBaseW();
	void makeBaseQ();
	double acc_noise, pos_noise, time_step;
};

