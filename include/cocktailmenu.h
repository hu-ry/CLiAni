//##############################################################################
//## Project: ClAni ########################### Created by hury on 20.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_COCKTAILMENU_H
#define CLIANIMATION_COCKTAILMENU_H

#include <menu.h>
#include <panel.h>
#include <map>

#include <utilz/global.h>


namespace CliAniHury {

#define CTRLD 4

    struct DcdMenu {
        int id;
        int items_Amount;
        MENU *menu;
        ITEM **items;

        explicit DcdMenu(int t_id, const char **t_labels, int t_amount)
                : id(t_id), items_Amount(t_amount) {
            items = new ITEM *[items_Amount + 1];
            for (int i = 0; i < items_Amount; ++i) {
                items[i] = new_item(t_labels[i], t_labels[i]);
            }
            items[items_Amount] = (ITEM *) NULL;
            menu = new_menu((ITEM **) items);
            //
            menu_opts_off(menu, O_SHOWDESC);
        }

        ~DcdMenu() {
            for (int i = 0; i < items_Amount; ++i) {
                free_item(items[i]);
            }
            free_menu(menu);

            delete[]items;
        }
    };

#define DCD_OP_MODE_AMOUNT 2

#define DCD_SCRLL_OPTION_AMOUNT 6
#define DCD_SCRLL_TASTE_AMOUNT 4
#define DCD_SCRLL_EFFECT_AMOUNT 5


#define DCD_FRAME_OPTION_AMOUNT 6
#define DCD_FRAME_TASTE_AMOUNT 3
#define DCD_FRAME_EFFECT_AMOUNT 2

// ---------------------Choose Operation Mode----------------------
    static const char *dcd_operation_modes[DCD_OP_MODE_AMOUNT] = {
            "Scroll Mode",
            "Frame Mode"
    };

// ---------------------Scroll Operation Mode----------------------
    static const char *dcd_scrll_opt_choices[DCD_SCRLL_OPTION_AMOUNT] = {
            "Start",
            "Flavour:",
            "Effect:",
            "Seed: ",
            "Variation:",
            "SHOW ME THE"
    };

    static const char *dcd_scrll_opt_default_selection[DCD_SCRLL_OPTION_AMOUNT] = {
            "",
            "Voronoi",
            "Scrolling",
            "1",
            ".:\"=edD#B@",
            "EXIT PLEASE!"
    };

    static const char *dcd_scrll_taste_choices[DCD_SCRLL_TASTE_AMOUNT] = {
            "Perlin Noise",
            "Voronoi",
            "Cell Voronoi",
            "Placeholder 1"
    };

    static const char *dcd_scrll_effect_choices[DCD_SCRLL_EFFECT_AMOUNT] = {
            "Scrolling",
            "Raining",
            "Zig-Zag",
            "Zig-Zag Legacy",
            "Static"
    };

// ---------------------Frame Operation Mode----------------------
    static const char *dcd_frame_opt_choices[DCD_FRAME_OPTION_AMOUNT] = {
            "Start",
            "Scene:",
            "Effect:",
            "Seed: ",
            "Variation:",
            "SHOW ME THE"
    };

    static const char *dcd_frame_opt_default_selection[DCD_FRAME_OPTION_AMOUNT] = {
            "",
            "Cube",
            "None",
            "1",
            ".:\"=edD#B@",
            "EXIT PLEASE!"
    };

    static const char *dcd_frame_taste_choices[DCD_FRAME_TASTE_AMOUNT] = {
            "Cube",
            "Placeholder 1",
            "Placeholder 2"
    };

    static const char *dcd_frame_effect_choices[DCD_FRAME_EFFECT_AMOUNT] = {
            "None",
            "Inverted"
    };

    enum DcdSlideOrigin{
        SLIDE_TOP,
        SLIDE_RIGHT,
        SLIDE_LEFT,
        SLIDE_BOT
    };


    class Decidecation {
    public:
        Decidecation();

        ~Decidecation();

        void runDecider(int *seed, char *variety, selection *select);

        /**
         * Enables a premature deallocation and/or exit of the menu
         */
        void abort();

        WINDOW *_HeaderWindow = nullptr;
        WINDOW *_OpModeWindow = nullptr;
        DcdMenu *_OpModeMenu = nullptr;

        WINDOW *createWin(int height, int width, int starty, int startx);
        void deleteWin(WINDOW *win_to_destroy);

        DcdMenu *createSlideMenu(WINDOW *destWin, DcdSlideOrigin origin);
        void deleteSlideMenu(WINDOW *destWin, DcdSlideOrigin origin);

    private:
        std::map<int, std::pair<bool, std::pair<WINDOW*, DcdMenu*>>> activeWins;


        WINDOW *_LeftOptWindow = nullptr;
        WINDOW *_RightOptWindow = nullptr;
        //DcdMenu(0, dcd_operation_modes, DCD_OP_MODE_AMOUNT);
        DcdMenu *_ScrllOptionMenu = nullptr;
        DcdMenu *_ScrllTasteMenu = nullptr;
        DcdMenu *_ScrllEffectMenu = nullptr;
        DcdMenu *_FrameOptionMenu = nullptr;
        DcdMenu *_FrameTasteMenu = nullptr;
        DcdMenu *_FrameEffectMenu = nullptr;

        void refreshAllWindows();

    };


}; // end of namespace CliAniHury

#endif //CLIANIMATION_COCKTAILMENU_H
