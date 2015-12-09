#define BOOST_TEST_MODULE ObserverGUI_test_module
#include <boost/test/included/unit_test.hpp>
#include "ObserverGUI.h"
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_generator)
BOOST_AUTO_TEST_CASE(testing_GUI_is_hard)
{
	ObserverGUI g;
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
