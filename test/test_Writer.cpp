
#define BOOST_TEST_MODULE Writer test module
#include <boost/test/included/unit_test.hpp>
#include "Writer.h"

using namespace boost::unit_test;


BOOST_AUTO_TEST_SUITE(test_Writer)
BOOST_AUTO_TEST_CASE(test_true)
{
	Writer Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()

