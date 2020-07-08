//##############################################################################
//## Project: ClAni ########################### Created by hury on 07.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <model/noisedef.h>

namespace tasty {

#define INDEX_SIZE 7U

    int noise_index[INDEX_SIZE] = {4, 29, 87, 12, 112, 65, 43};


    NoiseAttribute noise_scrolling(Flavour &flavour, int x, int y) {
        return flavour.generateNoise(x, y);
    }

    NoiseAttribute noise_raining(Flavour &flavour, int x, int y) {
        double temp = .0;
        for(int i=0; i < INDEX_SIZE; i++) {
            temp = flavour.generateNoise(noise_index[i], noise_index[INDEX_SIZE-1-i]);
            // TODO: Do some math with the noise to make rain
        }
        return .5;
    }

    NoiseAttribute noise_zigzag(Flavour &flavour, int x, int y) {
        return .5;
    }

}; // end of namespace tasty
