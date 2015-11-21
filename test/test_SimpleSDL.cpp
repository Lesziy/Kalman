
#define BOOST_TEST_MODULE SimpleSDL test module
#include <boost/test/included/unit_test.hpp>
#include "SimpleSDL.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(test_SimpleSDL)
BOOST_AUTO_TEST_CASE(test_true)
{
	SimpleSDL Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()

