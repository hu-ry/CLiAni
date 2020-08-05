//##############################################################################
//## Project: ClAni ########################### Created by hury on 28.06.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <glm/geometric.hpp>

#include <model/flavour/cellular.h>
#include <utilz/humath.h>


namespace tasty {

    // Hardcoded values for different shades
    float shades[10] = {0.09, 0.19, 0.29, 0.37,
    0.46, 0.55, 0.63, 0.7, 0.82, 9.0};

    double Cellular::generateNoise(int x, int y) {
        x = x % VORONOI_WIDTH;
        y = y % VORONOI_HEIGHT;

        int bottomLeft_X = (x - (x % VORONOI_GRID_SCALE));
        int bottomLeft_Y = (y - (y % VORONOI_GRID_SCALE));


        double minDist = VORONOI_GRID_SCALE;
        glm::vec2 minGrid = glm::vec2(1, 1);
        glm::vec2 minPoint = glm::vec2(1, 1);

        int maxTileX, maxTileY, tileX, tileY;

        // For checking bounds
        tileX = (bottomLeft_X / VORONOI_GRID_SCALE) - (bottomLeft_X != 0);
        tileY = (bottomLeft_Y / VORONOI_GRID_SCALE) - 1;

        maxTileX = (bottomLeft_X / VORONOI_GRID_SCALE)
                   + (bottomLeft_X + VORONOI_GRID_SCALE != VORONOI_WIDTH);
        maxTileY = (bottomLeft_Y / VORONOI_GRID_SCALE) + 1;

        // Calc voronoi pass for neighbour grid
        for (int yi = tileY; yi < maxTileY + 1; yi++) {
            for (int xi = tileX; xi < maxTileX + 1; xi++) {

                int index = xi + (VORONOI_GRID_WIDTH * yi);
                for (int i = 0; i < _Grid.at(index).fp_amount; i++) {
                    glm::vec2 rad;
                    glm::vec2 point;
                    point.x = _Grid.at(index).f_points[i].x;
                    point.y = _Grid.at(index).f_points[i].y;
                    rad.x = point.x + xi*VORONOI_GRID_SCALE - (float)x;
                    rad.y = fabsf(point.y + yi*VORONOI_GRID_SCALE) - y;

                    double dist = sqrt(glm::dot(rad, rad));
                    //double dist = glm::dot(rad, rad);

                    if (dist < minDist) {
                        // Saving closest distance
                        minDist = dist;
                        // Saving Closest Point
                        int temp;
                        if(index < 0) {
                            temp = (VORONOI_SQUARE_AMOUNT+index)%VORONOI_SQUARE_AMOUNT;
                        } else {
                            temp = index%VORONOI_SQUARE_AMOUNT;
                        }
                        minGrid = glm::vec2(temp, i);
                        minPoint = point;
                    }
                }
            }
        }

        float temp =    (minGrid.x/VORONOI_SQUARE_AMOUNT)+(minGrid.y*2)
                        + roundf(minPoint.y/VORONOI_GRID_SCALE);
        int shade_index = (int)roundf((temp/5)*10);

        double result = shades[shade_index];


        // (minPoint.x / VORONOI_GRID_SCALE + minPoint.y / VORONOI_GRID_SCALE)/2;
        // + (((minPoint.y / VORONOI_GRID_SCALE) * (minPoint.y / VORONOI_GRID_SCALE)) / 1.5);

        // !!!Unused Code!!!
        //glm::vec3 color = glm::mix( glm::vec3(1.0), glm::vec3(0.0), smoothstep( 0.03, 0.08, (float)result ) );
        //result = 0.2126*color.x + 0.7152*color.y + 0.0722*color.z; // grayscale

        return result; // WORKS NOW!
    }


    void Cellular::voronoi_pass(int xLocal, int yLocal, int xi, int yi,
                                double& minDist, glm::vec2& minGrid, glm::vec2& minRad) {

        int index = xi + (VORONOI_GRID_WIDTH * yi);
        for (int i = 0; i < _Grid.at(index).fp_amount; i++) {
            glm::vec2 rad;
            rad.x = _Grid.at(index).f_points[i].x + _Grid.at(index).bot_left.x - xLocal;
            rad.y = _Grid.at(index).f_points[i].y + yi*VORONOI_GRID_SCALE - yLocal;

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
            rad.y = _Grid.at(index).f_points[i].y + yi*VORONOI_GRID_SCALE - yLocal;


            if ( glm::dot(minRad-rad, minRad-rad)>1.00f) {
                minDist = glm::min((float)minDist, glm::dot( 0.5f*(minRad+rad), glm::normalize(rad-minRad) ));
            }
        }
        return minDist;
    }
}; // end of namespace tasty