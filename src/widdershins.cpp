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
        int opmode = _View->init();

        if(opmode == 0) {
            _View->fastExit();
        }

        _View->runMainMenu();

        _Engine.setCharacters(_View->getVariety(), SYMBOL_VARIETY);

        // Assigns wanted Scrollmode run function pointer in a branchless manner (really pls don't do this)
        // And yes I hate branch coverage :)
        _RunFunc = reinterpret_cast<opmode_run_func>(
                (opmode == 1) * reinterpret_cast<uint64_t>(scrollmode_run) +
                (opmode == 2) * reinterpret_cast<uint64_t>(framemode_run)
                );

        // Preparing model and noise functions for operating
        _Engine.setup(opmode, _View->getSeed(), _View->getSelection());
    }

    void Widdershins::runFrame(int time) {

        (*_RunFunc)(*_View, _Engine);

    }

    void scrollmode_run(CliView &view, GreaseMonkey &engine) {
        // Prints the newest line of characters at the top
        view.printAtNoRefresh(0, 0, engine.runIteration());
        // Waits for a specific amount of time
        view.waiting(100);
        // Removes the bottom most line on cli
        view.removeBottomLine();
    }

    void framemode_run(CliView &view, GreaseMonkey &engine) {
        view.printOverTopLeft(engine.runFrame());
        view.waiting(50);
    }

}; // end of namespace CliAniHury