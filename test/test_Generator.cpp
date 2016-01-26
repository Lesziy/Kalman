#define BOOST_TEST_MODULE Generator_tests
#include <boost/test/included/unit_test.hpp>
#include "Generator.h"
#include "../src/Generator/PythonFile.h"

using namespace boost::unit_test;
using namespace GeneratorUtil;

BOOST_AUTO_TEST_SUITE(PythonFile_tests)

BOOST_AUTO_TEST_CASE(FileNotFound)
{
	BOOST_REQUIRE_THROW(PythonFile pf("niegzgbzcbzxbgeddgdg.cvcvzxczxc"), std::exception);
}

BOOST_AUTO_TEST_CASE(classicUse)
{
	PythonFile pf("../../test/fixtures/Generator/SimpleScript.py");
	BOOST_REQUIRE_EQUAL(pf.ToString(), "def SimpleScript():\n    return (1,1)\n");
	BOOST_REQUIRE_EQUAL(pf.GetFunctionName(), "SimpleScript()");


	PythonFile pf2("../../maps/const.py");
	BOOST_REQUIRE_EQUAL(pf2.GetFunctionName(), "const()");
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Generator_tests)
BOOST_AUTO_TEST_CASE(classicUse)
{
	Generator g("../../maps/const.py");
	Status s = g.ThreadProc(0);

	BOOST_REQUIRE_EQUAL(s.x, 1);
	BOOST_REQUIRE_EQUAL(s.y, 1);
}
BOOST_AUTO_TEST_SUITE_END()
