//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
//##############################################################################
//## Project: ClAni ########################### Created by hury on 28.06.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <glm/vec3.hpp>

#include <model/flavour/cellular.h>
#include <utilz/humath.h>


namespace tasty {

    double Cellular::generateNoise(int x, int y) {
        int bottomLeft_X = (x - (x % VORONOI_GRID_SCALE));
        int bottomLeft_Y = (y - (y % VORONOI_GRID_SCALE));


        double minDist = VORONOI_GRID_SCALE;
        glm::vec2 minGrid, minRad;

        int maxTileX, maxTileY, tileX, tileY;

        // For checking bounds and literal SANITY CHECK!!!
        if (bottomLeft_X == 0) {
            tileX = bottomLeft_X / VORONOI_GRID_SCALE;
        } else {
            tileX = (bottomLeft_X / VORONOI_GRID_SCALE) - 1;
        }

        if (bottomLeft_Y == 0) {
            tileY = bottomLeft_Y / VORONOI_GRID_SCALE;
        } else {
            tileY = (bottomLeft_Y / VORONOI_GRID_SCALE) - 1;
        }

        if (bottomLeft_X + VORONOI_GRID_SCALE == VORONOI_WIDTH) {
            maxTileX = bottomLeft_X / VORONOI_GRID_SCALE;
        } else {
            maxTileX = (bottomLeft_X / VORONOI_GRID_SCALE) + 1;
        }

        if (bottomLeft_Y + VORONOI_GRID_SCALE == VORONOI_HEIGHT) {
            maxTileY = bottomLeft_Y / VORONOI_GRID_SCALE;
        } else {
            maxTileY = (bottomLeft_Y / VORONOI_GRID_SCALE) + 1;
        }

        // Calc first voronoi pass for neighbour grid
        for (int yi = tileY; yi < maxTileY + 1; yi++) {
            for (int xi = tileX; xi < maxTileX + 1; xi++) {
                // First PASS


            }
        }

        //tileX -= 1;
        //tileY -= 1;
        //maxTileX += 1;
        //maxTileY += 1;
        //
        //if(tileX < 0)
        //    tileX = 0;
        //if(tileY < 0)
        //    tileY = 0;
        //if(maxTileX >= VORONOI_GRID_WIDTH)
        //    maxTileX -= 1;
        //if(maxTileY >= VORONOI_GRID_HEIGHT)
        //    maxTileY -= 1;

        for (int yi = tileY; yi < maxTileY + 1; yi++) {
            for (int xi = tileX; xi < maxTileX + 1; xi++) {
                // Second PASS


            }
        }

        double result = minDist / VORONOI_GRID_SCALE;

        // !!!Unused Code!!!
        //glm::vec3 color = glm::mix( glm::vec3(1.0), glm::vec3(0.0), smoothstep( 0.03, 0.08, (float)result ) );
        //result = 0.2126*color.x + 0.7152*color.y + 0.0722*color.z;

        return result; // Doesn't work yet :C
    }


    void Cellular::voronoi_pass(int xLocal, int yLocal, int xi, int yi,
                                double& minDist, glm::vec2& minGrid, glm::vec2& minRad) {

        int index = xi + (VORONOI_GRID_WIDTH * yi);
        for (int i = 0; i < _Grid.at(index).fp_amount; i++) {
            glm::vec2 rad;
            rad.x = _Grid.at(index).f_points[i].x + _Grid.at(index).bot_left.x - xLocal;
            rad.y = _Grid.at(index).f_points[i].y + _Grid.at(index).bot_left.y - yLocal;

            //double dist = sqrt(dot_prod(xRad, yRad, xRad, yRad));
            double dist = glm::dot(rad, rad);

            if (dist < minDist) {
                minRad = rad;
                minGrid = glm::vec2(xi, yi);
                minDist = dist;
            }
        }
    }

    double Cellular::distance_pass(int xLocal, int yLocal, int xi, int yi,
                                   double minDist, glm::vec2& minGrid, glm::vec2& minRad) {

        int index = xi + (VORONOI_GRID_WIDTH * yi);
        for (int i = 0; i < _Grid.at(index).fp_amount; i++) {
            glm::vec2 rad;
            rad.x = _Grid.at(index).f_points[i].x + _Grid.at(index).bot_left.x - xLocal;
            rad.y = _Grid.at(index).f_points[i].y + _Grid.at(index).bot_left.y - yLocal;


            if ( glm::dot(minRad-rad, minRad-rad)>1.00f) {
                minDist = glm::min((float)minDist, glm::dot( 0.5f*(minRad+rad), glm::normalize(rad-minRad) ));
            }
        }
        return minDist;
    }
}; // end of namespace tasty