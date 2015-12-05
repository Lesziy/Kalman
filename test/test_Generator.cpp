#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>
#include "Generator.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_pythonfile)
BOOST_AUTO_TEST_CASE(pythonfile_filenotfound)
{
	BOOST_REQUIRE_THROW(Generator g("niegzgbzcbzxbgeddgdg.cvcvzxczxc"), std::exception);
}
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(test_generator)
BOOST_AUTO_TEST_CASE(test_true)
{
//	Generator g("plik.txt");
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
