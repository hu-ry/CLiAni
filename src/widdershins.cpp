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

        // Scrollmode run function pointer assigned
        _RunFunc = scrollmode_run;

        // Preparing model and noise functions for operating
        _Engine.setup(seed, _View->getSelection(), 0);
    }

    void Widdershins::runFrame(int time) {

        (*_RunFunc)(*_View, _Engine);

    }

    void scrollmode_run(CliView &view, GreaseMonkey &engine) {
        // Prints the newest line of characters at the top
        view.printAt(0, 0, engine.runIteration());
        // Waits for a specific amount of time
        view.waiting(100);
        // Removes the bottom most line on cli
        view.removeBottomLine();
    }

    void framemode_run(CliView &view, GreaseMonkey &engine) {


        view.waiting(50);
    }

}; // end of namespace CliAniHury