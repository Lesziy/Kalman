
#define BOOST_TEST_MODULE Kalman_tests
#include <boost/test/included/unit_test.hpp>
#include "KalmanFilter.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(KalmanFilter_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	KalmanFilter Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
