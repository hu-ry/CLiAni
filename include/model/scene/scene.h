//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.08.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_SCENE_H
#define CLIANIMATION_SCENE_H

#include <utilz/humath.h>
#include <cstdint>
#include <tuple>

namespace tasty {

    struct Camera{
        humath::v3f Position = humath::v3f(.0,.0,.0);
        struct {
            float yaw = 0.0;
            float pitch = 0.0;
        } Direction;
        float POV = 3.14159 / 5.0;
    };

    class Scene {
    public:

        Scene(uint32_t t_height, uint32_t t_width) {
            m_FrameSize = t_height*t_width;
            m_Dimension = {t_height, t_width};
            m_Frame = new float[t_height*t_width];
        }
        virtual ~Scene() {
            delete[]m_Frame;
        }

        virtual float *calcFrame() {
            return nullptr;
        }

        virtual const char *transFrame() {
            return nullptr;
        }

    protected:
        uint32_t m_FrameSize = 0;
        // Dimensions{Height, Width}
        struct {
            uint32_t height = 0;
            uint32_t width = 0;
        } m_Dimension;
        float* m_Frame = nullptr;

    };

    class Scene2D : Scene {
    public:
        Scene2D(uint32_t t_height, uint32_t t_width) : Scene(t_height, t_width) {

        }
    };

    class Scene3D : Scene {
    public:
        Scene3D(uint32_t t_height, uint32_t t_width) : Scene(t_height, t_width) {

        }

    protected:
        Camera m_Camera;
        humath::mat3f m_ViewMatrix;
        humath::mat3f m_ProjectionMatrix;
        humath::mat3f m_WorldMatrix;
    };

}; // end of namespace tasty

#endif //CLIANIMATION_SCENE_H
