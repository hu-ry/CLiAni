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
        int width = 0;
        const char* title{};
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
        explicit DcdMenu(int t_id, const char **t_labels, const char **t_descs, int t_amount)
                : id(t_id), items_Amount(t_amount) {
            items = new ITEM *[items_Amount + 1];
            for (int i = 0; i < items_Amount; ++i) {
                items[i] = new_item(t_labels[i], t_descs[i]);
            }
            items[items_Amount] = (ITEM *) NULL;
            menu = new_menu((ITEM **) items);
        }

        ~DcdMenu() {
            free_menu(menu);
            for (int i = 0; i < items_Amount; ++i) {
                free_item(items[i]);
            }

            delete[]items;
        }
    };

#define DCD_MENU_WIDTH 40
#define DCD_MENU_HEIGHT 16
#define DCD_MENU_MAX_LABEL_SIZE 14

#define DCD_OP_MODE_AMOUNT 2

#define DCD_SCRLL_OPTION_AMOUNT 6
#define DCD_SCRLL_TASTE_AMOUNT 4
#define DCD_SCRLL_EFFECT_AMOUNT 5


#define DCD_FRAME_OPTION_AMOUNT 6
#define DCD_FRAME_TASTE_AMOUNT 3
#define DCD_FRAME_EFFECT_AMOUNT 2


    enum DcdSlideOrigin{
        SLIDE_TOP,
        SLIDE_RIGHT,
        SLIDE_LEFT,
        SLIDE_BOT
    };

    class DcdIconSkin {
    public:
        DcdIconSkin();
        DcdIconSkin(int t_height, int t_width);

        void drawIcon(WINDOW *win);

        const char* _Icon;

    private:
        int _Width = DCD_MENU_WIDTH;
        int _Height = DCD_MENU_HEIGHT;
    };


    /**
     * Decidecation is more or less a singleton class which handles the usage of
     * menu and windows of the ncurses library at the start of the program for
     * clani.
     *
     * @c This new word "Decidecation" is my part in contributing to the english
     * language through neologism
     */
    class Decidecation {
    public:
        Decidecation();

        ~Decidecation();

        int runStarter();

        /**
         *
         * @param seed
         * @param variety
         * @param select
         * @return 1 if successful and 0 for exit
         */
        int runDecider(char *seed, char *variety, selection *select);

        /**
         * Enables a premature deallocation and/or exit of the menu
         */
        void abort();

        WINDOW *_HeaderWindow = nullptr;
        WINDOW *_OpModeWindow = nullptr;

        DcdIconSkin *_ClaniBanner;

        WINDOW *createWin(int height, int width, int starty, int startx);
        void deleteWin(WINDOW *win_to_destroy);


    private:
        int _OperationMode = -1;
        int _Cols;
        int _Lines;

        char _InputSeed[INPUT_SEED_MAXLENGTH+1] = "1";
        char _InputVariety[SYMBOL_VARIETY+1];

        WINDOW *_LeftOptWindow = nullptr;
        WINDOW *_RightOptWindow = nullptr;

        DcdMenu *_ScrllOptionMenu = nullptr;
        DcdMenu *_ScrllTasteMenu = nullptr;
        DcdMenu *_ScrllEffectMenu = nullptr;
        DcdMenu *_FrameOptionMenu = nullptr;
        DcdMenu *_FrameTasteMenu = nullptr;
        DcdMenu *_FrameEffectMenu = nullptr;


        /**
         *
         * @param localMenu : current active menu
         * @param subWin : sub WINDOW which holds the items
         * @return -1 on exit or index from 0 - n for selected item
         */
        int runSelectMenu(DcdMenu *localMenu, WINDOW *subWin);

        void runSeedInput(DcdMenu *localMenu, WINDOW *subWin);
        void runVariationInput(DcdMenu *localMenu, WINDOW *subWin);

        /**
         * Draws the menu and his box in as a whole. Doesn't call refresh() nor
         * wrefresh().
         * @remark Menu should be posted first preferably before calling this!
         * @param win : pointer to menu WINDOW
         * @param title : string as caption for menu
         * @param width : int of width for menu window
         */
        void drawMenu(WINDOW *win, const char *title, int width);
        void onResize();
        void refreshAllWindows();

    };


}; // end of namespace CliAniHury

#endif //CLIANIMATION_COCKTAILMENU_H
