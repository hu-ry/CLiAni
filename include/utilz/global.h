//##############################################################################
//## Project: ClAni ########################### Created by hury on 26.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_GLOBAL_H
#define CLIANIMATION_GLOBAL_H

#define WINDOW_LINE_HEIGHT 40
#define WINDOW_LINE_WIDTH 120

enum e_Flavour{
    FLAVOUR_PERLIN = 0,
    FLAVOUR_VORONOI,
    FLAVOUR_CELLULAR,
    FLAVOUR_TYPE_1,
    FLAVOUR_GENERIC
};

enum e_NoiseAttribute{
    ATTRIBUTE_SCROLLING = 0,
    ATTRIBUTE_RAINING,
    ATTRIBUTE_ZIGZAG,
    ATTRIBUTE_ZIGZAG_LEGACY,
    ATTRIBUTE_STATIC,
    ATTRIBUTE_GENERIC
};

#endif //CLIANIMATION_GLOBAL_H
