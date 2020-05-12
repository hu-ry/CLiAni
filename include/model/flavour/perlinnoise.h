//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
//##############################################################################
//## Project: ClAni ########################### Created by hury on 02.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_PERLINNOISE_H
#define CLIANIMATION_PERLINNOISE_H

#include <model/flavour/flavour.h>


#define NOISE_GRID_SCALE 16
#define NOISE_WIDTH 128
#define NOISE_HEIGHT 256
#define NOISE_GRID_WIDTH (NOISE_WIDTH / NOISE_GRID_SCALE)
#define NOISE_GRID_HEIGHT (NOISE_HEIGHT / NOISE_GRID_SCALE)

#define NOISE_GRADIENTS_AMOUNT ((NOISE_GRID_WIDTH+1)*(NOISE_GRID_HEIGHT+1))

namespace tasty {

    class PerlinNoise : public Flavour {
    public:
        explicit PerlinNoise(int seed) {
            _Gradients = new Vec2D[_GradSize];
            generate_gradients(seed);
        }

        PerlinNoise(const PerlinNoise &obj) { // copy constructor
            _Gradients = new Vec2D[_GradSize];
            *_Gradients = *obj._Gradients; // copy the value
        }

        ~PerlinNoise() override {
            delete[]_Gradients;
        }

        double generateNoise(int x, int y) override;

        double genPerlinNoise(int x_cord, int y_cord, Vec2D *gradients);


    private:
        Vec2D *_Gradients;
        static const int _GradSize = NOISE_GRADIENTS_AMOUNT;


        void generate_gradients(unsigned int seed);

        double calc_dot_grid_gradient(
                double internX,
                double internY,
                int x,
                int y,
                Vec2D *gradients
        );
    };
}; // end of namespace tasty

#endif //CLIANIMATION_PERLINNOISE_H