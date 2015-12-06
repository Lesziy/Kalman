#define BOOST_TEST_MODULE Generator tests
#include <boost/test/included/unit_test.hpp>
#include "Generator.h"
#include "../src/Generator/PythonFile.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(test_pythonfile)

BOOST_AUTO_TEST_CASE(pythonFile_FileNotFound)
{ 
	BOOST_REQUIRE_THROW(PythonFile pf("niegzgbzcbzxbgeddgdg.cvcvzxczxc"), std::exception);
}

BOOST_AUTO_TEST_CASE(pythonfile_classicUse)
{
	PythonFile pf("test/fixtures/Generator/SimpleScript.py");
	BOOST_REQUIRE_EQUAL(pf.ToString(), "def update():\n    return (1,1)\n");

}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(test_generator)
BOOST_AUTO_TEST_CASE(test_true)
{
//	Generator g("plik.txt");
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
