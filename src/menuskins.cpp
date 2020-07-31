//##############################################################################
//## Project: ClAni ########################### Created by hury on 31.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <cocktailmenu.h>

namespace CliAniHury {

    const char* dcd_isometric_clani_banner = {
            "      ___           ___       ___           ___                 \n"
            "     /\\  \\         /\\__\\     /\\  \\         /\\__\\          ___   \n"
            "    /::\\  \\       /:/  /    /::\\  \\       /::|  |        /\\  \\  \n"
            "   /:/\\:\\  \\     /:/  /    /:/\\:\\  \\     /:|:|  |        \\:\\  \\ \n"
            "  /:/  \\:\\  \\   /:/  /    /::\\~\\:\\  \\   /:/|:|  |__      /::\\__\\\n"
            " /:/__/ \\:\\__\\ /:/__/    /:/\\:\\ \\:\\__\\ /:/ |:| /\\__\\  __/:/\\/__/\n"
            " \\:\\  \\  \\/__/ \\:\\  \\    \\/__\\:\\/:/  / \\/__|:|/:/  / /\\/:/  /   \n"
            "  \\:\\  \\        \\:\\  \\        \\::/  /      |:/:/  /  \\::/__/    \n"
            "   \\:\\  \\        \\:\\  \\       /:/  /       |::/  /    \\:\\__\\    \n"
            "    \\:\\__\\        \\:\\__\\     /:/  /        /:/  /      \\/__/    \n"
            "     \\/__/         \\/__/     \\/__/         \\/__/                "
    };

    const char* dcd_icon_earth = {
            "BBBBBBBBBBBBBBBBBBBNNBBBBBBBBBBBBBBBBBBB"
            "BBBBBBBBBBB$X)<**1\"^\"\"\"\\?{SmQBBBBBBBBBBB"
            "BBBBBBBQX*~` .__..-!\"^\"r^^+xehHNBBBBBBBB"
            "BBBBBg?. `-`_!<^~~--```-!17exxe%QBBBBBBB"
            "BBBBh_``.-!</\"-__~``.``._!yXPyyX@NBBBBBB"
            "BBBX_--. .~!^_^_\"^..\"__^\"!^\"?4mp@QBBBBBB"
            "BBg!~^!1___:^!*(?/^-\"?-\"]aex!x%D$QBBBBBB"
            "BB91\"\"/t|\"!+1\"_^_^_^<>^_-_\"3A{km0NBBBBBB"
            "BB6r\"\"**x{?t{<:  ^7oX}?!~\"+rPSG$QBBBBBBB"
            "BB&\"!\"_*iIyoyI3\" `<ux/~:\"l{s69qQNBBBBBBB"
            "BBBk^!rcjjoSajJ_ -x]!\"\"ok6k%m@gNBBBBBBBB"
            "BBBBK\"rt|?7]SX]^-|jjIxew6%mq$QBBBBBBBBBB"
            "BBBBBNXL?1^_\\tey7<LeyoS4%H@gNBBBBBBBBBBB"
            "BBBBBBBB$XzL*\"+sSSyjeX9m$QNBBBBBBBBBBBBB"
            "BBBBBBBBBBBN$mhXaShmD$QNBBBBBBBBBBBBBBBB"
            "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
    };

    DcdIconSkin::DcdIconSkin() {
        _Icon = dcd_icon_earth;
    }

    DcdIconSkin::DcdIconSkin(int t_height, int t_width) {
        _Width = t_width;
        _Height = t_height;
        _Icon = dcd_isometric_clani_banner;
    }

    void DcdIconSkin::drawIcon(WINDOW *win) {
        mvwprintw(win, 0, 0, "%s", _Icon);
    }

}; // end of namespace CliAniHury