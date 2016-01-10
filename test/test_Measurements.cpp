
#define BOOST_TEST_MODULE Measurements_tests
#include <boost/test/included/unit_test.hpp>
#include "Measurements.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(Measurements_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	Measurements Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
