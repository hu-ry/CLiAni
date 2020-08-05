//##############################################################################
//## Project: ClAni ########################### Created by hury on 26.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_GLOBAL_H
#define CLIANIMATION_GLOBAL_H

#define WINDOW_LINE_HEIGHT 40
#define WINDOW_LINE_WIDTH 120

#define INPUT_SEED_MAXLENGTH 8
#define SYMBOL_VARIETY 10

#define KEY_ALT_BACKSPACE 127

union selection {
    int option_l;
    struct {
        short taste;
        short effect;
    } option_s;
};

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

enum e_Scene{
    SCENE_TYPE_1 = 0,
    SCENE_CUBE,
    SCENE_TYPE_2
};

enum e_SceneEffect{
    EFFECT_NONE = 0,
    EFFECT_INVERTED,
    EFFECT_TYPE_1
};

#endif //CLIANIMATION_GLOBAL_H
