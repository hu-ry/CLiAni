//##############################################################################
//## Project: ClAni ########################### Created by hury on 20.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_COCKTAILMENU_H
#define CLIANIMATION_COCKTAILMENU_H

#include <menu.h>
#include <panel.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

typedef struct DcdMenu{
    int id;
    int items_Amount;
    MENU *menu;
    ITEM **items;
    DcdMenu() {

    }
    ~DcdMenu() {

    }

};

#define DCD_SCRLL_OPTION_AMOUNT 6
#define DCD_SCRLL_TASTE_AMOUNT 4
#define DCD_SCRLL_EFFECT_AMOUNT 5


#define DCD_FRAME_OPTION_AMOUNT 6
#define DCD_FRAME_TASTE_AMOUNT 3
#define DCD_FRAME_EFFECT_AMOUNT 2

// ---------------------Scroll Operation Mode----------------------
const char *dcd_scrll_opt_choices[DCD_SCRLL_OPTION_AMOUNT] = {
        "Start",
        "Flavour:",
        "Effect:",
        "Seed: ",
        "Variation:",
        "SHOW ME THE"
};

const char *dcd_scrll_opt_default_selection[DCD_SCRLL_OPTION_AMOUNT] = {
        "",
        "Voronoi",
        "Scrolling",
        "1",
        ".:\"=edD#B@",
        "EXIT PLEASE!"
};

const char *dcd_scrll_taste_choices[DCD_SCRLL_TASTE_AMOUNT] = {
        "Perlin Noise",
        "Voronoi",
        "Cell Voronoi",
        "Placeholder 1"
};

const char *dcd_scrll_effect_choices[DCD_SCRLL_EFFECT_AMOUNT] = {
        "Scrolling",
        "Raining",
        "Zig-Zag",
        "Zig-Zag Legacy",
        "Static"
};

// ---------------------Frame Operation Mode----------------------
const char *dcd_frame_opt_choices[DCD_FRAME_OPTION_AMOUNT] = {
        "Start",
        "Scene:",
        "Effect:",
        "Seed: ",
        "Variation:",
        "SHOW ME THE"
};

const char *dcd_frame_opt_default_selection[DCD_FRAME_OPTION_AMOUNT] = {
        "",
        "Cube",
        "None",
        "1",
        ".:\"=edD#B@",
        "EXIT PLEASE!"
};

const char *dcd_frame_taste_choices[DCD_FRAME_TASTE_AMOUNT] = {
        "Cube",
        "Placeholder 1",
        "Placeholder 2"
};

const char *dcd_frame_effect_choices[DCD_FRAME_EFFECT_AMOUNT] = {
        "None",
        "Inverted"
};


class Decidecation {
public:
    Decidecation();
    ~Decidecation();

    WINDOW *_HeaderWindow;
    WINDOW *_OpModeWindow;

    WINDOW *_LeftOptWindow;
    WINDOW *_RightOptWindow;

private:

};




#endif //CLIANIMATION_COCKTAILMENU_H
