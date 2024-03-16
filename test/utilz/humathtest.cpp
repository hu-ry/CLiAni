//##############################################################################
//## Project: cliAnimation ###################### Created by hury on 29.10.20 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#define BOOST_TEST_MODULE UnitTest MathTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "humath.h"

struct fixture {
    int aa;
    long bb;
};

BOOST_AUTO_TEST_CASE(cosine_interpolate_test) {

}

BOOST_FIXTURE_TEST_CASE(fix, fixture) { int cc = aa; }