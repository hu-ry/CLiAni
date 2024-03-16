//##############################################################################
//## Project: ClAni ############################# Created by hury on 16.03.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include "scene/cubescene.h"

namespace tasty {

    CubeScene::CubeScene(uint32_t t_height, uint32_t t_width)
        : Scene3D(t_height, t_width) {
        m_Camera.Position = {0.0, -200.0, 0.0};

        std::string sMesh = "0"; // TODO: Enter valid string
        m_tracer.load_mesh_from_string(sMesh);
    }


} // end of namespace tasty