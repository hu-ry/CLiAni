//
// Created by hury on 28.06.20.
//

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
        void voronoi_pass(int xLocal, int yLocal, int xi, int yi,
                double& minDist, glm::vec2& minGrid, glm::vec2& minRad);
        double distance_pass(int xLocal, int yLocal, int xi, int yi,
                double minDist, glm::vec2& minGrid, glm::vec2& minRad);

    };

}; // end of namespace tasty
#endif //CLIANIMATION_CELLULAR_H