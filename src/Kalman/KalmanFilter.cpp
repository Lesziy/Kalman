#include "KalmanFilter.h"
#include <ctime>



KalmanFilter::KalmanFilter() 
{
}

KalmanFilter::~KalmanFilter()
{
}

void KalmanFilter::makeBaseA() {
	A(1, 1) = 1.0;
	A(1, 2) = time_step;
	A(2, 1) = 0.0;
	A(2, 2) = 1.0;
};
void KalmanFilter::makeBaseB() {
	B(1, 1) = time_step * time_step / 2;
	B(2, 1) = time_step;
};
void KalmanFilter::makeBaseH() {
	H(1, 1) = 1;
	H(1, 2) = 0;
};
void KalmanFilter::makeBaseV() {
	V(1, 1) = 1.0;
};
void KalmanFilter::makeBaseR() {
	R(1, 1) = pos_noise * pos_noise;
};
void KalmanFilter::makeBaseW() {
	W(1, 1) = 1.0;
	W(1, 2) = 0.0;
	W(2, 1) = 0.0;
	W(2, 2) = 1.0;
};
void KalmanFilter::makeBaseQ() {
	Q(1, 1) = time_step*time_step*time_step*time_step / 4 * acc_noise * acc_noise;
	Q(1, 2) = time_step*time_step*time_step / 2 * acc_noise * acc_noise;
	Q(2, 1) = time_step*time_step*time_step / 2 * acc_noise * acc_noise;
	Q(2, 2) = time_step*time_step       * acc_noise * acc_noise;
};




Status KalmanFilter::ThreadProc(Status s)
{
	s.type = KALMAN;
	/*
	
		Obliczenia

	*/
	return s;
}