#define BOOST_TEST_MODULE Common_tests
#include <boost/test/included/unit_test.hpp>
#include <functional>
#include "Common.h"

using namespace boost::unit_test;
using namespace CommonUtil;




BOOST_AUTO_TEST_SUITE(Common_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	Common Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
