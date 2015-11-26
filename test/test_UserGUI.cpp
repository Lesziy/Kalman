
#define BOOST_TEST_MODULE UserGUI test module
#include <boost/test/included/unit_test.hpp>
#include "UserGUI.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(test_UserGUI)
BOOST_AUTO_TEST_CASE(test_true)
{
	UserGUI Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()

