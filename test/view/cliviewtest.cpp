//##############################################################################
//## Project: cliAnimation ###################### Created by hury on 29.10.20 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#define BOOST_TEST_MODULE UnitTest Viewtest
#include <boost/test/unit_test.hpp>
#include <ncurses.h>

#include "cliview.h"

using namespace CliAniHury;

struct fixture {
    int aa;
    long bb;
};

BOOST_AUTO_TEST_CASE(ctors_good) {
    BOOST_CHECK_EQUAL(stdscr, nullptr);
}

BOOST_FIXTURE_TEST_CASE(fix, fixture) { int cc = aa; }