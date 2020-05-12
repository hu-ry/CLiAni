//╔═══════════════════════════════════════════════════════════════════════════════════════╗
//║▒░░▒▒░░▒▒▒░░▒▒▒░░▒▒░░▒▒▒▒░░▒▒▒░░▒▒▒▒▒▒▒░░▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒░░▒▒░░▒▒▒░░▒▒▒▒▒▒░░▒▒░░▒║
//╚═══════════════════════════════════════════════════════════════════════════════════════╝
//##############################################################################
//## Project: ClAni ########################### Created by hury on 18.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <cmath>
#include <model/noisedef.h>

#include <unistd.h>
#include <iostream>
#include <fstream>


inline double cosine_interpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * .5;

    return (a * (1 - f) + b * f);
}

void generate_gradients(Vec2D *gradients, int amount, unsigned int seed) {
    srandom(seed);

    for(int i=0; i<amount; i++) {
        gradients[i].x = cos((double)(random()%6));
        gradients[i].y = sin((double)(random()%6));
    }
}

inline double smooth(double t) {
    return (((6*t*t*t*t*t) - (15*t*t*t*t)) + (10*t*t*t));
}

double calc_dot_grid_gradient(
        double internX,
        double internY,
        int x,
        int y,
        Vec2D *gradients) {

    int index = x + ((NOISE_GRID_WIDTH+1) * y);
    //std::ofstream file("Debug.txt", std::ofstream::app);
    //file << "Index: " << index << " with X: " << x << " | " << y << " :Y"<< std::endl;

    return ((x-internX)*gradients[index].x)+((y-internY)*gradients[index].y);
}

double genPerlinNoise(int x_cord, int y_cord, Vec2D *gradients) {
    int bottomLeft_X = 0;
    int bottomLeft_Y = 0;

    if(x_cord==NOISE_WIDTH) {
        bottomLeft_X = x_cord-NOISE_GRID_SCALE;
    } else if(x_cord%NOISE_GRID_SCALE == 0) {
        bottomLeft_X = x_cord;
    } else {
        bottomLeft_X = (x_cord-(x_cord%NOISE_GRID_SCALE));
    }

    if(y_cord==NOISE_HEIGHT) {
        bottomLeft_Y = y_cord-NOISE_GRID_SCALE;
    } else if(y_cord%NOISE_GRID_SCALE == 0) {
        bottomLeft_Y = y_cord;
    } else {
        bottomLeft_Y = (y_cord-(y_cord%NOISE_GRID_SCALE));
    }

    GridRectangle grid{
        .tl=calc_dot_grid_gradient( // Top Left Corner
                (double)x_cord/NOISE_GRID_SCALE,
                (double)y_cord/NOISE_GRID_SCALE,
                bottomLeft_X/NOISE_GRID_SCALE,
                (bottomLeft_Y+NOISE_GRID_SCALE)/NOISE_GRID_SCALE,
                gradients
                ),
        .tr=calc_dot_grid_gradient( // Top Right Corner
                (double)x_cord/NOISE_GRID_SCALE,
                (double)y_cord/NOISE_GRID_SCALE,
                (bottomLeft_X+NOISE_GRID_SCALE)/NOISE_GRID_SCALE,
                (bottomLeft_Y+NOISE_GRID_SCALE)/NOISE_GRID_SCALE,
                gradients
                ),
        .bl=calc_dot_grid_gradient( // Bottom Left Corner
                (double)x_cord/NOISE_GRID_SCALE,
                (double)y_cord/NOISE_GRID_SCALE,
                bottomLeft_X/NOISE_GRID_SCALE,
                bottomLeft_Y/NOISE_GRID_SCALE,
                gradients
                ),
        .br=calc_dot_grid_gradient( // Bottom Right Corner
                (double)x_cord/NOISE_GRID_SCALE,
                (double)y_cord/NOISE_GRID_SCALE,
                (bottomLeft_X+NOISE_GRID_SCALE)/NOISE_GRID_SCALE,
                bottomLeft_Y/NOISE_GRID_SCALE,
                gradients
                )
    };


    double weight = smooth((double)abs(x_cord - bottomLeft_X)
            /NOISE_GRID_SCALE);

    double top = linear_inpo(grid.tl, grid.tr, weight);
    double bot = linear_inpo(grid.bl, grid.br, weight);

    weight = smooth((double)
            abs(y_cord - (bottomLeft_Y + NOISE_GRID_SCALE))
            / NOISE_GRID_SCALE);

    return (double)(linear_inpo(top, bot, weight)+1)/2;
}
