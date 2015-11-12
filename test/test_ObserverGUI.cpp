#define BOOST_TEST_MODULE test module name 2
#include <boost/test/included/unit_test.hpp>
#include "ObserverGUI.h"
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_generator)
BOOST_AUTO_TEST_CASE(test_true)
{
	ObserverGUI g;
	BOOST_TEST(true);
}
BOOST_AUTO_TEST_SUITE_END()
