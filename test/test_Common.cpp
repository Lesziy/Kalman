#define BOOST_TEST_MODULE Common_tests
#include <boost/test/included/unit_test.hpp>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include "Common.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/bind/placeholders.hpp>
using namespace boost::unit_test;
using namespace CommonUtil;

class Ping : public Observee
{
public:
    Ping()
    {

    }
    ~Ping()
    {

    }

    void setPosition(Status s)
    {
        status_ = s;
        signal_(status_);
    }
};


class Pong : public Observator
{

public:
    std::vector<int> data;
    int ok;
    Status ret;
    void other() {BOOST_LOG_TRIVIAL(trace) << "other"; ok = -500;}
    Pong() : ok(1)
    {
    };

    void update(Status s)
    {
        other();
        BOOST_LOG_TRIVIAL(trace) << "Pong update, x:" << s.x <<", y:" << s.y;
        data.push_back(1);
    }
};

BOOST_AUTO_TEST_SUITE(Common_tests)
BOOST_AUTO_TEST_CASE(test_true)
{
	Common Foo();
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Observee_Observer_tests)
BOOST_AUTO_TEST_CASE(classicUse)
{
    Ping ping;
    Pong pong;

    ping.connect(std::bind(&Pong::update, pong, std::placeholders::_1));
    ping.setPosition(Status(123.0, 0));



    BOOST_LOG_TRIVIAL(debug) << "pong.ok:" << pong.data.at(0);

    BOOST_REQUIRE(pong.ok);
}
BOOST_AUTO_TEST_SUITE_END()
