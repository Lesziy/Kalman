
#define BOOST_TEST_MODULE Kalman_tests
#include <boost/test/included/unit_test.hpp>
#include "KalmanFilter.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(KalmanFilter_tests)
BOOST_AUTO_TEST_CASE(simple_move)
{
	KalmanFilter_1D::Vector x(2);
	KalmanFilter_1D::Vector y(2);
	x(1) = 0.0;
	x(2) = 0.0;
	y(1) = 0.0;
	y(2) = 0.0;

	Status s;
	s.x = 0.0;
	s.y = 0.0;
	s.ax = 1.0;
	s.ay = 2.0;

	double _x, _y;
	double noise = 0.01;
	double step = 0.1;

	KalmanFilter kf(step, noise, 0.001, x, y);

	for (int i = 0; i < 8; ++i) {
		s = kf.ThreadProc(s);
		_x = s.ax * ((i + 1) * (i + 1) * step * step) / 2;
		_y = s.ay * ((i + 1) * (i + 1) * step * step) / 2;
		BOOST_CHECK(std::abs(s.x - _x) <= noise);
		BOOST_CHECK(std::abs(s.y - _y) <= noise);
		s.x = _x;
		s.y = _y;
	};
}

BOOST_AUTO_TEST_SUITE_END()
