#pragma once
#include "Common.h"
#include "KalmanFilter_1D.h"

using namespace CommonUtil;

class KalmanFilter : public Worker<Traits::InputOutputWorker>
{
    public:
        KalmanFilter(const double& time_step_, const double& pos_noise_, const double& acc_noise_,
					 KalmanFilter_1D::Vector& init_x, KalmanFilter_1D::Vector& init_y);
        ~KalmanFilter();

		Status ThreadProc(Status s);

	protected:

		KalmanFilter_1D x_Filter;
		KalmanFilter_1D y_Filter;
		KalmanFilter_1D::Vector ux, uy, zx, zy;
};

