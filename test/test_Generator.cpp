#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>
#include "Generator.h"
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_generator)
BOOST_AUTO_TEST_CASE(test_true)
{
	Generator g;
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
