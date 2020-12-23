//##############################################################################
//## Project: ClAni ########################### Created by hury on 28.06.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_CELLULAR_H
#define CLIANIMATION_CELLULAR_H

#include <model/flavour/voronoi.h>

namespace tasty {

    class Cellular : public Voronoi {
    public:
        explicit Cellular(int seed) : Voronoi(seed) {}

        ~Cellular() override = default;

        double generateNoise(int x, int y) override;

    protected:
        /**
         *
         * @deprecated !!!DEPRECATED AND UNUSED FUNCTION!!!
         *
         * @param xLocal : int current x pixel
         * @param yLocal : int current y pixel
         * @param xi : int x grid index of current grid
         * @param yi : int y grid index of current grid
         * @param minDist : minimum Distance
         * @param minGrid : minimum Grid indexes ?
         * @param minRad : minimum radius
         */
        void voronoi_pass(int xLocal, int yLocal, int xi, int yi,
                double& minDist, humath::v2f& minGrid, humath::v2f& minRad);

        /**
         *
         * @deprecated !!!DEPRECATED AND UNUSED FUNCTION!!!
         *
         * @param xLocal : int current x pixel
         * @param yLocal : int current y pixel
         * @param xi : int x grid index of current grid
         * @param yi : int y grid index of current grid
         * @param minDist : minimum Distance
         * @param minGrid : minimum Grid indexes ?
         * @param minRad : minimum radius
         * @return the final distance
         */
        double distance_pass(int xLocal, int yLocal, int xi, int yi,
                double minDist, humath::v2f& minGrid, humath::v2f& minRad);

    };

}; // end of namespace tasty
#endif //CLIANIMATION_CELLULAR_H