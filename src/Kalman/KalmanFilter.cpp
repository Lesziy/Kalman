#include "KalmanFilter.h"

using namespace std;


KalmanFilter::KalmanFilter(const double& time_step_, const double& pos_noise_, const double& acc_noise_, 
						   KalmanFilter_1D::Vector& init_x, KalmanFilter_1D::Vector& init_y) :
			  x_Filter(time_step_, pos_noise_, acc_noise_), y_Filter(time_step_, pos_noise_, acc_noise_), ux(1), uy(1), zx(1), zy(1)
{
	x_Filter.initFilter(init_x);
	y_Filter.initFilter(init_y);
}

KalmanFilter::~KalmanFilter()
{
}


Status KalmanFilter::ThreadProc(Status s)
{
	s.type = KALMAN;
	
	ux(1) = s.ax;
	uy(1) = s.ay;

	zx(1) = s.x;
	zy(1) = s.y; 

	x_Filter.step(ux, zx);
	y_Filter.step(uy, zy);

	s.x = x_Filter.getX()(1);
	s.y = y_Filter.getX()(1);
	
	return s;
}