//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_CLIVIEW_H
#define CLIANIMATION_CLIVIEW_H

#include <menu.h>

namespace CliAniHury {


    class CliView {
    public:
        CliView();
        ~CliView();

        void init();

        void removeBottomLine();
        void printAt(int x, int y, const char *printStr);
        void requestCharacters(char *input, int n);
        int requestUserSeed(char *input, int n);

        /**
         * UNUSED FUNCTION!
         */
        void drawAll();
        void waiting(int time);

        int getSelection();


    private:
        const char* _defaultChars = ".:\"=edD#B@_";

        int option_index = -1;
        int c;

        void runStartMenu();

        const char *choices[5] = {
                "Perlin Noise",
                "Voronoi",
                "Cell Voronoi",
                "Placeholder 2",
                "the Exit"
                };

        const char *effectChoices[5] = {
                "Scrolling",
                "Scrolling",
                "Scrolling",
                "Placeholder 2",
                "Just show me"
        };

    };

};
#endif //CLIANIMATION_CLIVIEW_H
