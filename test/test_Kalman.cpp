
#define BOOST_TEST_MODULE Kalman_tests
#include <boost/test/included/unit_test.hpp>
#include "Kalman.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(Kalman_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	Kalman Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
