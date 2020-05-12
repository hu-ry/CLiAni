//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_HUMATH_H
#define CLIANIMATION_HUMATH_H

#include <cmath>

#define linear_inpo(a0, a1, w) ((a0) + (w)*((a1) - (a0)))

inline double cosine_interpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * .5;

    return (a * (1 - f) + b * f);
}

inline double smooth(double t) {
    return (((6*t*t*t*t*t) - (15*t*t*t*t)) + (10*t*t*t));
}

inline double dot_prod(double x1, double y1, double x2, double y2) {
    return x1*x2+y1*y2;
}

#endif //CLIANIMATION_HUMATH_H
