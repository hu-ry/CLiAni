//##############################################################################
//## Project: ClAni ############################# Created by hury on 16.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_CUBESCENE_H
#define CLIANIMATION_CUBESCENE_H

#include "scene.h"
#include "utilz/raytracer.h"

namespace tasty {

    class CubeScene : Scene3D {
    public:
        CubeScene(uint32_t t_height, uint32_t t_width);


    private:
        Raytracer m_tracer;
    };

}
#endif //CLIANIMATION_CUBESCENE_H
