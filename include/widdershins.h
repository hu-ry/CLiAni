//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
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

    };
}; // end of namespace CliAniHury

#endif //CLIANIMATION_WIDDERSHINS_H
