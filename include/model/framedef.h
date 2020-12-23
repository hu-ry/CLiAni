//##############################################################################
//## Project: ClAni ########################### Created by hury on 05.08.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_FRAMEDEF_H
#define CLIANIMATION_FRAMEDEF_H

#include <utilz/global.h>
#include <model/scene/scene.h>

namespace tasty {

    class FrameIteration {
    public:
        FrameIteration();
        FrameIteration(int t_height, int t_width);
        ~FrameIteration();


    private:
        char* _currFrame;
        int _frameSize = WINDOW_LINE_HEIGHT*WINDOW_LINE_WIDTH;
        int _currentRow = 0; // current row in frame?
    };


}; // end of namespace tasty

#endif //CLIANIMATION_FRAMEDEF_H
