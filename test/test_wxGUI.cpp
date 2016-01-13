#define BOOST_TEST_MODULE wxGUI_tests
#include <boost/test/included/unit_test.hpp>
//#include "wxGUI.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(wxGUI_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
//	wxGUI Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
