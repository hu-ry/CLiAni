//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_WIDDERSHINS_H
#define CLIANIMATION_WIDDERSHINS_H

#include "cliview.h"
#include "model/greasemonkey.h"

namespace CliAniHury {

    void scrollmode_run(CliView &view, GreaseMonkey &engine);
    void framemode_run(CliView &view, GreaseMonkey &engine);

    typedef void (*opmode_run_func) (CliView &, GreaseMonkey &);

    class Widdershins {
    public:
        Widdershins();
        ~Widdershins();

        void registerCliView(CliView *view) {this->_View = view;}
        int exit();

        void start();
        void runFrame(int time);


    private:
        CliView* _View;
        GreaseMonkey _Engine;
        opmode_run_func _RunFunc = nullptr;

    };
}; // end of namespace CliAniHury

#endif //CLIANIMATION_WIDDERSHINS_H
