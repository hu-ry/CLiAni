//##############################################################################
//## Project: ClAni ########################### Created by hury on 21.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <cocktailmenu.h>

namespace CliAniHury {

    Decidecation::Decidecation() {

    }

    Decidecation::~Decidecation() {

    }

    void Decidecation::runDecider(int *seed, char *variety, selection *select) {

    }

    void Decidecation::abort() {

    }






    WINDOW* Decidecation::createWin(int height, int width, int starty, int startx) {

        return nullptr;
    }

    void Decidecation::deleteWin(WINDOW *win_to_destroy) {

    }

    DcdMenu* Decidecation::createSlideMenu(WINDOW *destWin, DcdSlideOrigin origin) {

        return nullptr;
    }

    void Decidecation::deleteSlideMenu(WINDOW *destWin, DcdSlideOrigin origin) {

    }


    void Decidecation::refreshAllWindows() {
        wrefresh(_HeaderWindow);
        if(_LeftOptWindow == nullptr && _RightOptWindow == nullptr) {
            wrefresh(_OpModeWindow);
        } else {
            wrefresh(_LeftOptWindow);
            wrefresh(_RightOptWindow);
        }
    }


}; // end of namespace CliAniHury