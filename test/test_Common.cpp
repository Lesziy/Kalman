#define BOOST_TEST_MODULE Common_tests
#include <boost/test/included/unit_test.hpp>
#include <functional>
#include "Common.h"

using namespace boost::unit_test;
using namespace CommonUtil;


class Ping : public Observee
{
public:
    Ping() { }

    void setPosition(Status s)
    {
        status_ = s;
        signal_(status_);
    }
};

class Pong : public Observator
{

public:
    bool ok;
    Pong() : ok(false) { };

    void update(Status s)
    {
        if(s.x == 123.0)
            ok = true;
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

    ping.connect(std::bind(&Pong::update, std::ref(pong), std::placeholders::_1));
    ping.setPosition(Status(123.0, 0));

    BOOST_REQUIRE(pong.ok);
}
BOOST_AUTO_TEST_SUITE_END()
