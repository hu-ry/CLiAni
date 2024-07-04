//##############################################################################
//## Project: ClAni ############################# Created by hury on 27.06.24 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_RAYTRACER_THREADSAFE_H
#define CLIANIMATION_RAYTRACER_THREADSAFE_H

#include <raytracer.h>

class ThreadsafeRaytracer {
public:
struct ConstantGlobalData {
    size_t m_MeshCount = 0;
    std::vector<Raytracer::Mesh> m_Meshes;
    uint32_t m_WindowHeight;
    uint32_t m_WindowWidth;
};

struct GlobalData {
    std::shared_ptr<tasty::Camera> m_Camera;
    std::vector<humath::v3f> m_RayAngles;

};


private:



};

#endif //CLIANIMATION_RAYTRACER_THREADSAFE_H
