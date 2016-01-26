
#define BOOST_TEST_MODULE Writer test module
#include <boost/test/included/unit_test.hpp>
#include <cstdio>
#include <fstream>

#include "Writer.h"
#include "Common.h"

using namespace boost::unit_test;
using namespace CommonUtil;

BOOST_AUTO_TEST_SUITE(Writer_tests)
BOOST_AUTO_TEST_CASE(classic_use)
{
	std::string test_file = std::tmpnam(nullptr);
	std::string source;
	BOOST_LOG_TRIVIAL(trace) << "Selected file name:" << test_file;
	Writer Foo(test_file, ';');
	//Status(double px, double py, double ax_, double ay_, long long ptime, Type who) : x(px), y(py), ax(ax_), ay(ay_), time(ptime), type(who) {};
	Status	s1(0, 1, 0, 0, 0, GENERATOR), 
			s2(2, 3, 0, 0, 0, SENSORS), 
			s3(4, 5, 0, 0, 0, KALMAN);

	Foo.ThreadProc(s1); 
	Foo.ThreadProc(s2);
	Foo.ThreadProc(s3);
	
	std::ifstream ifs(test_file);

	BOOST_REQUIRE(ifs);
	BOOST_REQUIRE(!ifs.bad());
	
	source.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

	BOOST_REQUIRE_EQUAL(source, "Generator x;Generator y;Sensor x;Sensor y;Kalman x;Kalman y\n0;1;2;3;4;5;\n");
}
BOOST_AUTO_TEST_SUITE_END()

