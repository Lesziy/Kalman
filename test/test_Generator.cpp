#define BOOST_TEST_MODULE Generator_tests
#include <boost/test/included/unit_test.hpp>
#include "Generator.h"
#include "../src/Generator/PythonFile.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(PythonFile_tests)

BOOST_AUTO_TEST_CASE(FileNotFound)
{
	BOOST_REQUIRE_THROW(PythonFile pf("niegzgbzcbzxbgeddgdg.cvcvzxczxc"), std::exception);
}

BOOST_AUTO_TEST_CASE(classicUse)
{
	PythonFile pf("test/fixtures/Generator/SimpleScript.py");
	BOOST_REQUIRE_EQUAL(pf.ToString(), "def SimpleScript():\n    return (1,1)\n");
	BOOST_REQUIRE_EQUAL(pf.GetFunctionName(), "SimpleScript()");


	PythonFile pf2("maps/standard.py");
	BOOST_REQUIRE_EQUAL(pf2.GetFunctionName(), "standard()");
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Generator_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
//	Generator g("plik.txt");
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
