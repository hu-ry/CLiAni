//##############################################################################
//## Project: ClAni ########################### Created by hury on 18.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <model/flavour/perlinnoise.h>
#include <utilz/humath.h>
#include <cstdlib>

namespace tasty {

    double PerlinNoise::generateNoise(int x, int y) {
        return genPerlinNoise(x, y, _Gradients);
    }

    void PerlinNoise::generate_gradients(unsigned int seed) {
        srand(seed);

        for (int i = 0; i < _GradSize; i++) {
            _Gradients[i].x = cos((double) (rand() % 6));
            _Gradients[i].y = sin((double) (rand() % 6));
        }
    }


    double PerlinNoise::calc_dot_grid_gradient(
            double internX,
            double internY,
            int x,
            int y,
            Vec2D *gradients) {

        int index = x + ((NOISE_GRID_WIDTH + 1) * y);

        return ((x - internX) * gradients[index].x) + ((y - internY) * gradients[index].y);
    }

    double PerlinNoise::genPerlinNoise(int x_cord, int y_cord, Vec2D *gradients) {
        x_cord = x_cord % NOISE_WIDTH;
        y_cord = y_cord % NOISE_WIDTH;

        int bottomLeft_X = (x_cord - (x_cord % NOISE_GRID_SCALE));
        int bottomLeft_Y = (y_cord - (y_cord % NOISE_GRID_SCALE));

        GridRectangle grid{
                .tl=calc_dot_grid_gradient( // Top Left Corner
                        (double) x_cord / NOISE_GRID_SCALE,
                        (double) y_cord / NOISE_GRID_SCALE,
                        bottomLeft_X / NOISE_GRID_SCALE,
                        (bottomLeft_Y + NOISE_GRID_SCALE) / NOISE_GRID_SCALE,
                        gradients
                ),
                .tr=calc_dot_grid_gradient( // Top Right Corner
                        (double) x_cord / NOISE_GRID_SCALE,
                        (double) y_cord / NOISE_GRID_SCALE,
                        (bottomLeft_X + NOISE_GRID_SCALE) / NOISE_GRID_SCALE,
                        (bottomLeft_Y + NOISE_GRID_SCALE) / NOISE_GRID_SCALE,
                        gradients
                ),
                .bl=calc_dot_grid_gradient( // Bottom Left Corner
                        (double) x_cord / NOISE_GRID_SCALE,
                        (double) y_cord / NOISE_GRID_SCALE,
                        bottomLeft_X / NOISE_GRID_SCALE,
                        bottomLeft_Y / NOISE_GRID_SCALE,
                        gradients
                ),
                .br=calc_dot_grid_gradient( // Bottom Right Corner
                        (double) x_cord / NOISE_GRID_SCALE,
                        (double) y_cord / NOISE_GRID_SCALE,
                        (bottomLeft_X + NOISE_GRID_SCALE) / NOISE_GRID_SCALE,
                        bottomLeft_Y / NOISE_GRID_SCALE,
                        gradients
                )
        };


        double weight = smooth((double)std::abs(x_cord - bottomLeft_X)
                               / NOISE_GRID_SCALE);

        double top = linear_inpo(grid.tl, grid.tr, weight);
        double bot = linear_inpo(grid.bl, grid.br, weight);

        weight = smooth((double)std::abs(y_cord - (bottomLeft_Y + NOISE_GRID_SCALE))
                        / NOISE_GRID_SCALE);

        return (linear_inpo(top, bot, weight) + 1.0) / 2.0;
    }
}; // end of namespace tasty