//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.08.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_SCENE_H
#define CLIANIMATION_SCENE_H

#include <utilz/humath.h>

namespace tasty {

    struct Camera{
        humath::v3f Position = humath::v3f(.0,.0,.0);
        humath::v3f Target = humath::v3f(.0,.0,.0);
        float POV = 3.14159 / 5.0;
    };

    class Scene {
    public:

        Scene(uint32_t t_height, uint32_t t_width) {
            _FrameSize = t_height*t_width;
            _Dimension = {t_height, t_width};
            _Frame = new float[t_height*t_width];
        }
        virtual ~Scene() {
            delete[]_Frame;
        }

        virtual float *calcFrame() {
            return nullptr;
        }

        virtual const char *transFrame() {
            return nullptr;
        }

    protected:
        uint32_t _FrameSize = 0;
        // tuple<Height, Width>
        std::tuple<uint32_t, uint32_t> _Dimension{0, 0};
        float* _Frame = nullptr;

    };

    class SceneTwoD : Scene {
    public:
        SceneTwoD(uint32_t t_height, uint32_t t_width) : Scene(t_height, t_width) {

        }
    };

    class SceneThreeD : Scene {
    public:
        SceneThreeD(uint32_t t_height, uint32_t t_width) : Scene(t_height, t_width) {

        }

    protected:
        Camera _Camera;
        humath::mat3f _ViewMatrix;
        humath::mat3f _ProjectionMatrix;
        humath::mat3f _WorldMatrix;
    };

}; // end of namespace tasty

#endif //CLIANIMATION_SCENE_H
