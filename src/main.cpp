//##############################################################################
//## Project: ClAni ########################### Created by hury on 29.01.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <iostream>
#include <csignal>
#include <atomic>

#include <widdershins.h>
#include <utilz/hutime.h>

std::atomic<bool> quit(false);
CliAniHury::Widdershins ctrl;

void got_signal(int signum) {
    if (signum == SIGWINCH)
        ctrl.scheduleResize();
    else if (signum == SIGINT)
        quit.store(true);
}


    int main(int argc, char* argv[]) {

        struct sigaction sigInt;
        // Binding Ctrl+C to got_signal() for normal shutdown
        sigInt.sa_handler = got_signal;
        sigemptyset(&sigInt.sa_mask);
        sigInt.sa_flags = 0;

        sigaction(SIGINT, &sigInt, NULL);
        sigaction(SIGWINCH, &sigInt, NULL);

        CliAniHury::CliView hr_view;

        // Registers View-module at ctrl for ncurses usage
        ctrl.registerCliView(&hr_view);
        // Update the window size once in the beginning to fit the terminal
        ctrl.scheduleResize();
        // Starts program with requesting user input and preparing modules
        ctrl.start();

        // Timer for getting deltaTime between iterations
        CliAniHury::HuTime curTime;
        int deltaTime, lastTime = curTime.millisec();

        while (!quit) {
            int currentTime = curTime.millisec();
            deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            // runs a "frame"
            ctrl.runFrame(deltaTime);

        }
        ctrl.exit();

        exit(SIGINT);
    }

