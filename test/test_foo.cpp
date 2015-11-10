#define BOOST_TEST_MODULE TEST_FOO
#include <boost/test/included/unit_test.hpp>
#include "Foo.h"
BOOST_TEST_SUITE( foo )

BOOST_AUTO_TEST_CASE( test_WhatIsLife )
{
      Foo f;
      BOOST_TEST( f.WhatIsLife() == 42 );
}

BOOST_AUTO_TEST_SUITE_END()
