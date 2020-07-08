//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <widdershins.h>
#include <cstdio>

namespace CliAniHury {

    Widdershins::Widdershins() {

        //printf("Created instance of Widdershins!\n");
    }

    Widdershins::~Widdershins() {

        //printf("Deleted instance of Widdershins!\n");
    }

    int Widdershins::exit() {
        _View->~CliView();
        _Engine.~GreaseMonkey();

        fflush(NULL);
        return 0;
    }

    void Widdershins::start() {
        // Sets up commandline for output
        _View->init();

        int n = MAX_INPUT_CHAR;
        char uinput2[n];
        // Asks User for optional character variation
        _View->requestCharacters(uinput2, n);
        _Engine.setCharacters(uinput2, n);

        n = 8;
        char uinput1[n];
        // Asks User for an optional Seed
        int seed = _View->requestUserSeed(uinput1, n);
        // Preparing model and noise functions for operating
        _Engine.setup(seed, _View->getSelection(), 1);
    }

    void Widdershins::runFrame(int time) {
        // Prints the newest line of characters at the top
        _View->printAt(0, 0, _Engine.runIteration());
        // Waits for a specific amount of time
        _View->waiting(time);
        // Removes the bottom most line on cli
        _View->removeBottomLine();
    }

}; // end of namespace CliAniHury