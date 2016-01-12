
#define BOOST_TEST_MODULE Sensors_tests
#include <boost/test/included/unit_test.hpp>
#include "Sensors.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(Sensors_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	Sensors Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
