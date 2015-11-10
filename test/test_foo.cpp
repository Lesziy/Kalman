#define BOOST_TEST_MODULE TEST_FOO
#include <boost/test/included/unit_test.hpp>
#include "Foo.h"
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_Foo )
BOOST_AUTO_TEST_CASE( test_WhatIsLife )
{
      Foo f;
      BOOST_TEST( f.WhatIsLife() == 42 );
}
BOOST_AUTO_TEST_CASE( LifeIsSad )
{
      Foo f;
      BOOST_TEST( f.WhatIsLife() == 41 );
}
BOOST_AUTO_TEST_SUITE_END()
