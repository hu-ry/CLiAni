//##############################################################################
//## Project: ClAni ########################### Created by hury on 07.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <model/noisedef.h>
#include <cmath>

namespace tasty {

#define DELETION_INTERVAL 5U



    NoiseAttribute noise_scrolling(Flavour &flavour, int x, int y) {
        return flavour.generateNoise(x, y);
    }

    bool att_raining_isInit = false;
    int att_raining_noise_pop[CHAR_AMOUNT_PER_LINE] = { };
    int att_raining_current_y = -1;
    unsigned int att_raining_curr_noise_count = 0;

    NoiseAttribute noise_raining(Flavour &flavour, int x, int y) {
        //if(y%6 == 0 && !att_raining_isInit) { // every 6 y's the noise array gets new random values
        //    int entropy = (int)random();
        //    // seeding inital population
        //    for(unsigned int i = 0; i < INDEX_SIZE; i++) {
        //        //temp = modf((double)entropy/1000, nullptr);
        //        att_raining_noise[i] = entropy;
        //    }
        //    att_raining_isInit = true;
        //} else {
        //    att_raining_isInit = false;
        //}

        if(att_raining_current_y != y) {
            att_raining_current_y = y;
            att_raining_noise_pop[ (int)random()%CHAR_AMOUNT_PER_LINE ] = 1;
            att_raining_curr_noise_count = (att_raining_curr_noise_count+1)%DELETION_INTERVAL;
            if(att_raining_curr_noise_count == 0) {
                att_raining_noise_pop[ (int)random()%CHAR_AMOUNT_PER_LINE ] = 0;
            }
        }


        if(att_raining_noise_pop[( x % CHAR_AMOUNT_PER_LINE )] == 1) {
            return flavour.generateNoise(x, y);
        } else {
            return 0.0;
        }

        // TODO: Do some math with the noise to make rain
        //if(entropy%4 != 0 || y%4 == 0) {
        //    result = flavour.generateNoise(noise[x%6]%120 ,noise[y%6]%120);
        //} else {
        //    result = 0.0;
        //}
    }

    NoiseAttribute noise_zigzag(Flavour &flavour, int x, int y) {
        return .5;
    }

    NoiseAttribute noise_static(Flavour &flavour, int x, int y) {
        int entropy = (int)random();
        if((entropy%6) == 0) {
            return flavour.generateNoise(entropy%120 ,y);
        } else {
            return 0.0;
        }
    }

}; // end of namespace tasty
