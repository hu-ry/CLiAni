//##############################################################################
//## Project: cliAnimation ###################### Created by hury on 29.10.20 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#define BOOST_TEST_MODULE UnitTest Greasemonkeytest
#include <boost/test/unit_test.hpp>

#include "greasemonkey.h"

struct fixture {
    int aa;
    long bb;
};

// Test for default constructor
BOOST_AUTO_TEST_CASE(default_ctor) {

}

// Tests for correct function of Greasemonkey::setup()
BOOST_AUTO_TEST_CASE(setup_test) {

}

// Test Testcase for external structures
BOOST_FIXTURE_TEST_CASE(fix, fixture)
{
    int cc = aa;
}