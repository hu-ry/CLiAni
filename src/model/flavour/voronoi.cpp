//##############################################################################
//## Project: ClAni ########################### Created by hury on 02.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <model/flavour/voronoi.h>
#include <utilz/humath.h>

namespace tasty {

    double Voronoi::generateNoise(int x, int y) {
        x = x % VORONOI_WIDTH;
        y = y % VORONOI_HEIGHT;

        int bottomLeft_X = (x - (x % VORONOI_GRID_SCALE));
        int bottomLeft_Y = (y - (y % VORONOI_GRID_SCALE));

        double minDist = VORONOI_GRID_SCALE;

        int maxTileX, maxTileY, tileX, tileY;

        // For checking bounds
        tileX = (bottomLeft_X / VORONOI_GRID_SCALE) - (bottomLeft_X != 0);
        tileY = (bottomLeft_Y / VORONOI_GRID_SCALE) - 1;

        maxTileX = (bottomLeft_X / VORONOI_GRID_SCALE)
                 + (bottomLeft_X + VORONOI_GRID_SCALE != VORONOI_WIDTH);
        maxTileY = (bottomLeft_Y / VORONOI_GRID_SCALE) + 1;

        // Calc closest point through neighbouring grids
        for (int yi = tileY; yi < maxTileY + 1; yi++) {
            for (int xi = tileX; xi < maxTileX + 1; xi++) {
                minDist = closest_point(x, y, minDist, xi, yi);
            }
        }
        double result = (minDist / VORONOI_GRID_SCALE);

        return result;
    }


    void Voronoi::generate_grid(SquareEntity* grid) {
        for (int y = 0; y < VORONOI_GRID_HEIGHT + 1; y++) {
            for (int x = 0; x < VORONOI_GRID_WIDTH + 1; x++) {
                _GridCorners[x + ((VORONOI_GRID_WIDTH + 1) * y)].x =
                        x * VORONOI_GRID_SCALE;
                _GridCorners[x + ((VORONOI_GRID_WIDTH + 1) * y)].y =
                        y * VORONOI_GRID_SCALE;
            }
        }
        for (int y = 0; y < VORONOI_GRID_HEIGHT; y++) {
            for (int x = 0; x < VORONOI_GRID_WIDTH; x++) {
                grid[x + (VORONOI_GRID_WIDTH * y)].bot_left.x =
                        x * VORONOI_GRID_SCALE;
                grid[x + (VORONOI_GRID_WIDTH * y)].bot_left.y =
                        y * VORONOI_GRID_SCALE;
            }
        }
    }

    void Voronoi::precompute_prob_amount(unsigned int seed, int max) {
        srandom(seed);
        for (int i = 0; i < max; i++) {
            _ProbabilityAmount[i] = (int) (1 + (random() % VORONOI_MAX_FPOINT_SQUARE));
        }
    }

    void Voronoi::generate_fpoints(SquareEntity* grid) {
        for (int i = 0; i < _SquareAmount; i++) {
            grid[i].fp_amount =
                    _ProbabilityAmount[random() % VORONOI_FP_PROBABILITIES];
            for (auto &f_point : grid[i].f_points) {
                f_point.x =
                        fabs(cos((double) (random() % 250))) * VORONOI_GRID_SCALE;
                f_point.y =
                        fabs(sin((double) (random() % 250))) * VORONOI_GRID_SCALE;
            }
        }
    }


    double Voronoi::closest_point(int x, int y, double minDist, int xi, int yi) {

        int index = xi + (VORONOI_GRID_WIDTH * yi);
        for (int i = 0; i < _Grid.at(index).fp_amount; i++) {
            double subx = _Grid.at(index).f_points[i].x + _Grid.at(index).bot_left.x - x;
            double suby = fabs(_Grid.at(index).f_points[i].y + yi*VORONOI_GRID_SCALE) - y;
            double dist = sqrt(dot_prod(subx, suby, subx, suby));
            minDist = minDist > dist ? dist : minDist;
        }
        return minDist;
    }
}; // end of namespace tasty