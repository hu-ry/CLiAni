//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_CLIVIEW_H
#define CLIANIMATION_CLIVIEW_H

namespace CliAniHury {


    class CliView {
    public:
        CliView();
        ~CliView();

        /**
         * Initializes ncurses and runs the start menu asking user for op mode
         *
         * @return 0 if successful and exit, 1 for scroll mode and 2 for frame mode
         */
        int init();
        void runMainMenu();
        void fastExit();

        void removeBottomLine();
        void printAt(int x, int y, const char *printStr);
        void requestCharacters(char *input, int n);
        int requestUserSeed(char *input, int n);

        /**
         * @deprecated UNUSED FUNCTION!
         */
        void drawAll();
        void waiting(int time);

        int getSelection();


    private:
        const char* _defaultChars = ".:\"=edD#B@_";
        void* _MainMenu;

        int option_index = -1;
        int c;

        /**
         * @deprecated Old clani menu. Do not use anymore!
         */
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
