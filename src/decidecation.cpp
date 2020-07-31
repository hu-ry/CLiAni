//##############################################################################
//## Project: ClAni ########################### Created by hury on 21.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <cocktailmenu.h>
#include <cstring>
#include <utilz/global.h>

namespace CliAniHury {

#define CTRLD   4

    // ---------------------Choose Operation Mode----------------------
    static const char *dcd_operation_modes[DCD_OP_MODE_AMOUNT] = {
            "Scroll Mode",
            "Frame Mode (Coming Soon!)"
    };

    // ---------------------Scroll Operation Mode----------------------
    const char *dcd_scrll_opt_choices[DCD_SCRLL_OPTION_AMOUNT] = {
            "Start",
            "Flavour:",
            "Effect:",
            "Seed: ",
            "Variation:",
            "EXIT         "
    };

    const char *dcd_scrll_opt_default_selection[DCD_SCRLL_OPTION_AMOUNT] = {
            "",
            "Voronoi",
            "Scrolling",
            "1",
            ".:\"=edD#B@",
            "              "
    };

    const char *dcd_scrll_taste_choices[DCD_SCRLL_TASTE_AMOUNT] = {
            "Perlin Noise",
            "Voronoi",
            "Cell Voronoi",
            "Placeholder 1"
    };

    const char *dcd_scrll_effect_choices[DCD_SCRLL_EFFECT_AMOUNT] = {
            "Scrolling",
            "Raining",
            "Zig-Zag",
            "Zig-Zag(OLD)",
            "Static"
    };

// ---------------------Frame Operation Mode----------------------
    const char *dcd_frame_opt_choices[DCD_FRAME_OPTION_AMOUNT] = {
            "Start",
            "Scene:",
            "Effect:",
            "Seed:",
            "Variation:",
            "SHOW ME THE"
    };

    const char *dcd_frame_opt_default_selection[DCD_FRAME_OPTION_AMOUNT] = {
            "",
            "Cube",
            "None",
            "1",
            ".:\"=edD#B@",
            "EXIT PLEASE!"
    };

    const char *dcd_frame_taste_choices[DCD_FRAME_TASTE_AMOUNT] = {
            "Placeholder 1",
            "Cube",
            "Placeholder 2"
    };

    const char *dcd_frame_effect_choices[DCD_FRAME_EFFECT_AMOUNT] = {
            "None",
            "Inverted"
    };

    Decidecation::Decidecation() {
        this->_Cols = COLS;
        this->_Lines = LINES;
        _ClaniBanner = new DcdIconSkin(10, 64);
    }

    Decidecation::~Decidecation() {
        delete _ClaniBanner;
    }

    int Decidecation::runStarter() {
        int max_y = this->_Lines;
        int max_x = this->_Cols;


        int headerHeight = 14;
        int headerWidth = 66;
        _HeaderWindow = createWin(headerHeight, headerWidth, 2, max_x/2 - headerWidth/2);

        int opHeight = 8;
        int opWidth = 39;
        const char* opTitle = "Select Operation Mode";
        _OpModeWindow = createWin(opHeight, opWidth, headerHeight + 2, max_x / 2 - opWidth / 2);

        DcdMenu opMenu = DcdMenu(0, dcd_operation_modes, DCD_OP_MODE_AMOUNT);
        set_menu_mark(opMenu.menu, " -> ");

        set_menu_win(opMenu.menu, _OpModeWindow);
        WINDOW* opModeSubWin = derwin(_OpModeWindow, opHeight - 4, opWidth - 7, 4, 3);
        set_menu_sub(opMenu.menu, opModeSubWin);
        box(_OpModeWindow, 0, 0);

        refresh();

        post_menu(opMenu.menu);

        _ClaniBanner->drawIcon(_HeaderWindow);
        drawMenu(_OpModeWindow, opTitle, opWidth);
        mvprintw(max_y - 2, 0, "F1 to EXIT and CTRL+C to exit during runtime");
        mvprintw(0, max_x - 15, "Made by hury :D");

        wrefresh(_HeaderWindow);
        wrefresh(_OpModeWindow);

        int c, enter = 0;
        while(enter == 0 && (c = getch()) != KEY_F(1)) {
            switch(c) {
                case KEY_RESIZE:
                    clear();
                    getmaxyx(stdscr, max_y, max_x);
                    mvwin(_OpModeWindow, headerHeight + 2, max_x < opWidth ? 0 : max_x / 2 - opWidth / 2);
                    mvwin(_HeaderWindow, 2, max_x < headerWidth ? 0 : max_x / 2 - headerWidth / 2);
                    break;
                case KEY_DOWN:
                    clear();
                    menu_driver(opMenu.menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    clear();
                    menu_driver(opMenu.menu, REQ_UP_ITEM);
                    break;
                case KEY_ENTER:
                case '\n':
                    clear();
                    menu_driver(opMenu.menu, REQ_TOGGLE_ITEM);
                    c = item_index(current_item(opMenu.menu));
                    napms(10);
                    enter++;
                    break;
            }
            _ClaniBanner->drawIcon(_HeaderWindow);
            drawMenu(_OpModeWindow, opTitle, opWidth);

            mvprintw(max_y - 2, 0, "F1 to EXIT and CTRL+C to exit during runtime");
            mvprintw(0, max_x-15, "Made by hury :D");
            refresh();
            wrefresh(_HeaderWindow);
            wrefresh(_OpModeWindow);
        }

        unpost_menu(opMenu.menu);

        clear();
        refresh();
        delwin(opModeSubWin);
        deleteWin(_OpModeWindow);

        this->_OperationMode = (c != KEY_F(1)) + c*(c != KEY_F(1));
        return this->_OperationMode;
    }

    int Decidecation::runDecider(char *seed, char *variety, selection *select) {
        getmaxyx(stdscr, this->_Lines, this->_Cols);

        int leftHeight = DCD_MENU_HEIGHT-2;
        int leftWidth = DCD_MENU_WIDTH;
        const char* leftTitle = "Choose";
        int leftStartX =  (_Cols/2)/2 - leftWidth/2;
        _LeftOptWindow = createWin(leftHeight, leftWidth, _HeaderWindow->_maxy+2, leftStartX);

        int rightHeight = DCD_MENU_HEIGHT;
        int rightWidth = DCD_MENU_WIDTH;
        const char* scrllTasteTitle = "Select Taste:";
        const char* scrllEffectTitle = "Select Attribute:";
        const char* frameTasteTitle = "Select Scene:";
        const char* frameEffectTitle = "Select Effect:";
        int rightStartX = (_Cols/2)/2 + (_Cols/2) - rightWidth/2;
        _RightOptWindow = createWin(rightHeight, rightWidth, _HeaderWindow->_maxy+2, rightStartX);

        DcdIconSkin rightOptIcon = DcdIconSkin();

        int exit = 0;


        if(_OperationMode == 1) {
            _ScrllOptionMenu = new DcdMenu(0, dcd_scrll_opt_choices, dcd_scrll_opt_default_selection, DCD_SCRLL_OPTION_AMOUNT);
            _ScrllOptionMenu->width = leftWidth;
            _ScrllOptionMenu->title = leftTitle;
            set_menu_mark(_ScrllOptionMenu->menu, " -> ");
            set_menu_win(_ScrllOptionMenu->menu, _LeftOptWindow);
            WINDOW* optionSubWin = derwin(_LeftOptWindow, leftHeight - 6, leftWidth - 4, 5, 2);
            set_menu_sub(_ScrllOptionMenu->menu, optionSubWin);

            _ScrllTasteMenu = new DcdMenu(1, dcd_scrll_taste_choices, DCD_SCRLL_TASTE_AMOUNT);
            _ScrllTasteMenu->width = rightWidth;
            _ScrllTasteMenu->title = scrllTasteTitle;
            set_menu_mark(_ScrllTasteMenu->menu, " -> ");
            set_menu_win(_ScrllTasteMenu->menu, _RightOptWindow);
            WINDOW* tasteSubWin = derwin(_RightOptWindow, rightHeight - 4, rightWidth - 20, 4, 9);
            set_menu_sub(_ScrllTasteMenu->menu, tasteSubWin);

            _ScrllEffectMenu = new DcdMenu(2, dcd_scrll_effect_choices, DCD_SCRLL_EFFECT_AMOUNT);
            _ScrllEffectMenu->width = rightWidth;
            _ScrllEffectMenu->title = scrllEffectTitle;
            set_menu_mark(_ScrllEffectMenu->menu, " -> ");
            set_menu_win(_ScrllEffectMenu->menu, _RightOptWindow);
            WINDOW* effectSubWin = derwin(_RightOptWindow, rightHeight - 4, rightWidth - 20, 4, 9);
            set_menu_sub(_ScrllEffectMenu->menu, effectSubWin);

            clear();
            post_menu(_ScrllOptionMenu->menu);

            _ClaniBanner->drawIcon(_HeaderWindow);
            drawMenu(_LeftOptWindow, leftTitle, leftWidth);
            rightOptIcon.drawIcon(_RightOptWindow);

            refresh();
            refreshAllWindows();

            int c, stop = 0;
            while(stop == 0 && (c = getch()) != KEY_F(1)) {
                switch (c) {
                    case KEY_RESIZE:
                        clear();
                        getmaxyx(stdscr, this->_Lines, this->_Cols);
                        //mvwin(_OpModeWindow, headerHeight + 2, max_x < opWidth ? 0 : max_x / 2 - opWidth / 2);
                        break;
                    case KEY_DOWN:
                        clear();
                        menu_driver(_ScrllOptionMenu->menu, REQ_DOWN_ITEM);
                        break;
                    case KEY_UP:
                        clear();
                        menu_driver(_ScrllOptionMenu->menu, REQ_UP_ITEM);
                        break;
                    case KEY_RIGHT:
                    case KEY_ENTER:
                    case '\n':
                        wclear(_RightOptWindow);
                        menu_driver(_ScrllOptionMenu->menu, REQ_TOGGLE_ITEM);
                        {
                            int item = item_index(current_item(_ScrllOptionMenu->menu));
                            switch(item) {
                                case 0:
                                    exit++;
                                    stop++;
                                    break;
                                case 1:
                                {
                                    item = runSelectMenu(_ScrllTasteMenu, tasteSubWin);
                                    select->option_s.taste =
                                            (item == -1) * select->option_s.taste
                                            + (item >= 0) * item;
                                    const char *tempLabel = dcd_scrll_taste_choices[select->option_s.taste];
                                    current_item(_ScrllOptionMenu->menu)->description.length = strlen(tempLabel);
                                    current_item(_ScrllOptionMenu->menu)->description.str = tempLabel;
                                    clear();
                                }
                                    break;
                                case 2: {
                                    item = runSelectMenu(_ScrllEffectMenu, effectSubWin);
                                    select->option_s.effect =
                                            (item == -1) * select->option_s.effect
                                            + (item >= 0) * item;
                                    const char *tempLabel = dcd_scrll_effect_choices[select->option_s.effect];
                                    current_item(_ScrllOptionMenu->menu)->description.length = strlen(tempLabel);
                                    current_item(_ScrllOptionMenu->menu)->description.str = tempLabel;
                                    clear();
                                }
                                    break;
                                case 3:
                                    runSeedInput(_ScrllOptionMenu, optionSubWin);
                                    current_item(_ScrllOptionMenu->menu)->description.length = INPUT_SEED_MAXLENGTH+1;
                                    current_item(_ScrllOptionMenu->menu)->description.str = _InputSeed;
                                    for(int i=0; i<INPUT_SEED_MAXLENGTH+1; i++) {
                                        seed[i] = _InputSeed[i];
                                    }
                                    break;
                                case 4:
                                    runVariationInput(_ScrllOptionMenu, optionSubWin);
                                    current_item(_ScrllOptionMenu->menu)->description.length = SYMBOL_VARIETY+1;
                                    current_item(_ScrllOptionMenu->menu)->description.str = _InputVariety;
                                    for(int i=0; i<SYMBOL_VARIETY+1; i++) {
                                        variety[i] = _InputVariety[i];
                                    }
                                    break;
                                case 5:
                                    stop++;
                                    break;
                                default:
                                    break;
                            }
                        }
                        napms(10);
                    break;
                    default:
                        break;
                }
                _ClaniBanner->drawIcon(_HeaderWindow);
                drawMenu(_LeftOptWindow, leftTitle, leftWidth);
                rightOptIcon.drawIcon(_RightOptWindow);

                refresh();
                refreshAllWindows();
            }
            unpost_menu(_ScrllOptionMenu->menu);

            delete _ScrllOptionMenu;
            delete _ScrllTasteMenu;
            delete _ScrllEffectMenu;

        } else if(_OperationMode == 2) {

        }


        clear();
        refresh();

        deleteWin(_LeftOptWindow);
        deleteWin(_RightOptWindow);
        deleteWin(_HeaderWindow);

        return exit;
    }

    void Decidecation::abort() {

    }


    WINDOW* Decidecation::createWin(int height, int width, int starty, int startx) {
        return newwin(height, width, starty, startx);
    }

    void Decidecation::deleteWin(WINDOW *win_to_destroy) {
        wborder(win_to_destroy, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(win_to_destroy);
        delwin(win_to_destroy);
        _OpModeWindow = nullptr;
    }

    int Decidecation::runSelectMenu(DcdMenu *localMenu, WINDOW *subWin) {
        post_menu(localMenu->menu);
        _ClaniBanner->drawIcon(_HeaderWindow);
        drawMenu(subWin->_parent, localMenu->title, localMenu->width);

        refresh();
        wrefresh(subWin->_parent);

        int c, stop = 0;
        while(stop == 0 && (c = getch())) {
            switch (c) {
                case KEY_RESIZE:
                    clear();
                    getmaxyx(stdscr, this->_Lines, this->_Cols);
                    break;
                case KEY_LEFT:
                case KEY_F(1):
                    clear();
                    c = -1;
                    stop++;
                    break;
                case KEY_DOWN:
                    clear();
                    menu_driver(localMenu->menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    clear();
                    menu_driver(localMenu->menu, REQ_UP_ITEM);
                    break;
                case KEY_ENTER:
                case '\n':
                    clear();
                    menu_driver(localMenu->menu, REQ_TOGGLE_ITEM);
                    c = item_index(current_item(localMenu->menu));
                    napms(10);
                    stop++;
                    break;
                default:
                    break;
            }
            _ClaniBanner->drawIcon(_HeaderWindow);
            drawMenu(subWin->_parent, localMenu->title, localMenu->width);
            drawMenu(_LeftOptWindow, _ScrllOptionMenu->title, _ScrllOptionMenu->width);

            refresh();
            refreshAllWindows();
        }
        unpost_menu(localMenu->menu);

        wclear(subWin);
        wrefresh(subWin);
        return c;
    }

    void Decidecation::runSeedInput(DcdMenu *localMenu, WINDOW *subWin) {
        int itemPosY = 3;
        int itemPosX = 16;

        const char* emptyField = {"        "};
        int backspace = ' ';
        mvwprintw(subWin, itemPosY, itemPosX, "%s", emptyField);
        wrefresh(subWin);

        char tempInput[INPUT_SEED_MAXLENGTH+1];
        int input_char, stop = 0;
        while(stop < INPUT_SEED_MAXLENGTH && (input_char = getch())) {
            if('0' <= input_char && input_char <= '9') {
                tempInput[stop] = (char)input_char;
                mvwprintw(subWin, itemPosY, itemPosX+stop, "%s", &input_char);
                stop++;
            }

            switch(input_char) {
                case KEY_BACKSPACE:
                case KEY_ALT_BACKSPACE:
                case '\b':
                    stop = stop - (stop > 0);
                    mvwprintw(subWin, itemPosY, itemPosX+stop, "%s", &backspace);
                    break;
                case KEY_ENTER:
                case '\n':
                    for(int k=stop; k<INPUT_SEED_MAXLENGTH+1; k++) {
                        tempInput[k] = '\0';
                    }
                    stop = INPUT_SEED_MAXLENGTH;
                    for(int i=0; i<INPUT_SEED_MAXLENGTH; i++) {
                        _InputSeed[i] = tempInput[i];
                    }
                    _InputSeed[INPUT_SEED_MAXLENGTH] = '\0';
                    break;
                case ERR:
                    stop = 1111;
                default:
                    break;
            }
            wrefresh(subWin);
        }

        if(stop != 1111) {
            tempInput[INPUT_SEED_MAXLENGTH] = '\0';
            for (int i = 0; i < INPUT_SEED_MAXLENGTH + 1; i++) {
                _InputSeed[i] = tempInput[i];
            }
        }
    }

    void Decidecation::runVariationInput(DcdMenu *localMenu, WINDOW *subWin) {
        int itemPosY = 4;
        int itemPosX = 16;

        const char* emptyField = {"          "};
        int backspace = ' ';
        mvwprintw(subWin, itemPosY, itemPosX, "%s", emptyField);
        wrefresh(subWin);

        char tempInput[SYMBOL_VARIETY+1];
        int input_char, stop = 0;
        while(stop < SYMBOL_VARIETY && (input_char = getch())) {
            if(' ' <= input_char && input_char <= '~') {
                tempInput[stop] = (char)input_char;
                mvwprintw(subWin, itemPosY, itemPosX+stop, "%s", &input_char);
                stop++;
            }

            switch(input_char) {
                case KEY_BACKSPACE:
                case KEY_ALT_BACKSPACE:
                case '\b':
                    stop = stop - (stop > 0);
                    mvwprintw(subWin, itemPosY, itemPosX+stop, "%s", &backspace);
                    break;
                //case KEY_ENTER:
                //case '\n':
                //    for(int k=stop; k<SYMBOL_VARIETY+1; k++) {
                //        tempInput[k] = '\0';
                //    }
                //    stop = SYMBOL_VARIETY;
                //    for(int i=0; i<SYMBOL_VARIETY; i++) {
                //        _InputVariety[i] = tempInput[i];
                //    }
                //    _InputVariety[SYMBOL_VARIETY] = '\0';
                //    break;
                case ERR:
                    stop = 1111;
                default:
                    break;
            }
            wrefresh(subWin);
        }

        if(stop != 1111) {
            tempInput[SYMBOL_VARIETY] = '\0';
            for(int i=0; i<SYMBOL_VARIETY+1; i++) {
                _InputVariety[i] = tempInput[i];
            }
        }
    }

    void Decidecation::drawMenu(WINDOW *win, const char *title, int width) {
        int length, x, y;
        float temp;

        x = 0;
        y = 1;

        length = strlen(title);
        temp = (width - length) / 2;

        int tmp = x + (int) temp;
        mvwprintw(win, y, tmp, "%s", title);
        box(win, 0, 0);
        mvwaddch(win, y + 1, x, ACS_LTEE);
        mvwhline(win, y + 1, x + 1, ACS_HLINE, width - 2);
        mvwaddch(win, y + 1, width - 1, ACS_RTEE);
    }

    void Decidecation::onResize() {

    }

    void Decidecation::refreshAllWindows() {
        wrefresh(_HeaderWindow);
        wrefresh(_LeftOptWindow);
        wrefresh(_RightOptWindow);
    }


}; // end of namespace CliAniHury