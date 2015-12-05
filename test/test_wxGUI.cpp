#define BOOST_TEST_MODULE wxGUI test module
#include <boost/test/included/unit_test.hpp>
//#include "wxGUI.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(test_wxGUI)
BOOST_AUTO_TEST_CASE(test_true)
{
//	wxGUI Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()

