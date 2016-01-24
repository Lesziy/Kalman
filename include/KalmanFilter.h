#pragma once
#include "Common.h"
#include <kalman/ekfilter.hpp>
#include <kalman/kfilter.hpp>


class KalmanFilter : public Worker<CommonUtil::InputOutputWorker>, 
							Kalman::KFilter<double, 1, false, false, true>
{
    public:
        KalmanFilter();
        ~KalmanFilter();

		Status ThreadProc(Status s);

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

