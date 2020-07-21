//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <menu.h>
#include <cstdlib>

#include <cliview.h>
#include <utilz/global.h>
#include <cstring>


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4


namespace CliAniHury {

    int char_to_decimal(const char *c, int size) {
        int result = 0;
        int factor = 10;
        int base = 1;
        for(size=size-1; 0<size; size--) {
            result = (c[size] - '0') * base;
            base = factor*base;
        }
        return result;
    }

    CliView::CliView() {
        // starting curses
        initscr();


        //printf("Created instance of CliView!\n");
    }

    CliView::~CliView() {
        nocbreak();
        echo();
        clear();
        // exiting curses
        endwin();

        //printf("Deleted instance of CliView!\n");
    }

    void CliView::init() {
        // Disables line buffering from ncurses
        cbreak();
        // Disables echoing of user input
        noecho();
        // Clears the screen
        clear();
        // Stops displaying cursor
        curs_set(0);

        // Enable keyboard input and starting menu
        keypad(stdscr, TRUE);

        // Runs the StartMenu and handles all the user input
        runStartMenu();

        curs_set(1);
        clear();
        refresh();
    }

    void CliView::removeBottomLine() {
        // Deletes the bottom line
        move(WINDOW_LINE_HEIGHT,0);
        deleteln();
        // moves curser to 0,0
        move(0,0);
        // Makes changes visible
        refresh();
    }

    void CliView::printAt(int x, int y, const char *printStr) {
        // Adds new line on top
        move(0,0);
        insertln();
        // Prints String at specified position
        mvprintw(y, x, printStr);
        refresh();
    }

    void CliView::requestCharacters(char *input, int n) {
        echo();
        printw(_defaultChars);
        printw("\nInsert characters that should appear(ENTER for default): ");
        getnstr(input, n);
        noecho();
        napms(500);

        clear();
        if((input != nullptr) && (input[0] == '\0')) {
            for(int i=0; i < n; i++)
            input[i] = _defaultChars[i];
        }
    }

    int CliView::requestUserSeed(char *input, int n) {
        echo();
        printw("Please insert a Seed(press ENTER to skip): ");
        getnstr(input, n);
        noecho();
        napms(500);
        curs_set(0);
        clear();
        if((input != nullptr) && (input[0] == '\0')) {
            return 1;
        }
        return char_to_decimal(input, n);
    }

    void CliView::runStartMenu() {
        ITEM **optionItems;
        MENU *selMenu;
        WINDOW *optWindow;
        int n_choices, i;

        n_choices = ARRAY_SIZE(choices);
        optionItems = new ITEM*[n_choices + 1];
        //optionItems = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

        for(i = 0; i < n_choices; ++i) {
            optionItems[i] = new_item(effectChoices[i], choices[i]);
        }
        optionItems[n_choices] = (ITEM *)NULL;

        selMenu = new_menu((ITEM **)optionItems);

        // Creating an options window
        int widthW = 40;
        int heightW = 10;
        int xW = 20;
        int yW = 4;
        optWindow = newwin(heightW, widthW, yW, xW);
        keypad(optWindow, TRUE);

        // Sets main window and sub window to fit onto screen
        set_menu_win(selMenu, optWindow);
        set_menu_sub(selMenu, derwin(optWindow, heightW - 4, widthW - 2, 3, 1));

        // Marks the menu with an arrow
        set_menu_mark(selMenu, " -> ");

        // Prints a border around the options window
        box(optWindow, 0, 0);

        {

            int length, x, y;
            float temp;
            const char* title = "ClAni - Select a taste";

            x = 0;
            y = 1;

            length = strlen(title);
            temp = (widthW - length) / 2;

            int tmp = x + (int) temp;
            mvwprintw(optWindow, y, tmp, "%s", title);
            refresh();

            mvwaddch(optWindow, y+1, x, ACS_LTEE);
            mvwhline(optWindow, y+1, x+1, ACS_HLINE, widthW-2);
            mvwaddch(optWindow, y+1, widthW-1, ACS_RTEE);
        }

        mvprintw(LINES - 2, 0, "F1 to EXIT and CTRL+C to exit during runtime");
        mvprintw(0, COLS-15, "Made by hury :D");
        refresh();

        post_menu(selMenu);
        wrefresh(optWindow);

        {
            int enter = 0;
            while (enter == 0 && (c = getch()) != KEY_F(1)) {
                switch (c) {
                    case KEY_DOWN:
                        menu_driver(selMenu, REQ_DOWN_ITEM);
                        break;
                    case KEY_UP:
                        menu_driver(selMenu, REQ_UP_ITEM);
                        break;
                    case 10:
                        menu_driver(selMenu, REQ_TOGGLE_ITEM);
                        napms(10);
                        enter++;
                        break;
                }
                wrefresh(optWindow);
            }
        }
        option_index = item_index(current_item(selMenu));

        unpost_menu(selMenu);

        free_menu(selMenu);
        for(i = 0; i < n_choices; ++i) {
            free_item(optionItems[i]);
        }

        delete[]optionItems;


        wrefresh(optWindow);

        if(c == KEY_F(1) || option_index==4) {
            nocbreak();
            echo();
            clear();
            refresh();
            // exiting curses
            endwin();
            exit(0);
        }
    }

    void CliView::waiting(int time) {
        napms(100);
    }

    int CliView::getSelection() {
        return option_index;
    }

}; // end of namespace CliAniHury
