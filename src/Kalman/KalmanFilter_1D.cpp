#include "KalmanFilter_1D.h"


KalmanFilter_1D::KalmanFilter_1D(const double& time_step_, const double& pos_noise_, const double& acc_noise_)
{
	setDim(2, 1, 2, 1, 1);
	acc_noise = acc_noise_;
	pos_noise = pos_noise_;
	time_step = time_step_;
}

KalmanFilter_1D::~KalmanFilter_1D()
{
}

void KalmanFilter_1D::initFilter(Vector& init_x) {
	static const double _P0[] = { 
		time_step*time_step*time_step*time_step / 4 * acc_noise * acc_noise, time_step*time_step*time_step / 2 * acc_noise * acc_noise,
		time_step*time_step*time_step / 2 * acc_noise * acc_noise,           time_step*time_step * acc_noise * acc_noise, };
	Matrix P0(2, 2, _P0);
	// verify : x.size == n
	this->init(init_x, P0);
}

void KalmanFilter_1D::makeBaseA() {
	A(1, 1) = 1.0;
	A(1, 2) = time_step;
	A(2, 1) = 0.0;
	A(2, 2) = 1.0;
};
void KalmanFilter_1D::makeBaseB() {
	B(1, 1) = time_step * time_step / 2;
	B(2, 1) = time_step;
};
void KalmanFilter_1D::makeBaseH() {
	H(1, 1) = 1;
	H(1, 2) = 0;
};
void KalmanFilter_1D::makeBaseV() {
	V(1, 1) = 1.0;
};
void KalmanFilter_1D::makeBaseR() {
	R(1, 1) = pos_noise * pos_noise;
};
void KalmanFilter_1D::makeBaseW() {
	W(1, 1) = 1.0;
	W(1, 2) = 0.0;
	W(2, 1) = 0.0;
	W(2, 2) = 1.0;
};
void KalmanFilter_1D::makeBaseQ() {
	Q(1, 1) = time_step*time_step*time_step*time_step / 4 * acc_noise * acc_noise;
	Q(1, 2) = time_step*time_step*time_step / 2 * acc_noise * acc_noise;
	Q(2, 1) = time_step*time_step*time_step / 2 * acc_noise * acc_noise;
	Q(2, 2) = time_step*time_step       * acc_noise * acc_noise;
};