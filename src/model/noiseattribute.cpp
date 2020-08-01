//##############################################################################
//## Project: ClAni ########################### Created by hury on 07.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#include <model/noisedef.h>
#include <cmath>

namespace tasty {

#define DELETION_INTERVAL 5U
#define SATISFACTION_LIMIT 150


    NoiseAttribute noise_scrolling(Flavour &flavour, int x, int y) {
        return flavour.generateNoise(x, y);
    }

    int att_raining_noise_pop[CHAR_AMOUNT_PER_LINE] = { };
    int att_raining_current_y = -1;
    unsigned int att_raining_curr_noise_count = 0;

    NoiseAttribute noise_raining(Flavour &flavour, int x, int y) {
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
    }

    int att_zigzag_current_y = -1;
    int att_zigzag_global_offset = 0;
    int att_zigzag_global_direction = 1;
    int att_zigzag_amp = 4;

    // 0 : if current pop is enabled with either 0 if not and 1 if active
    // 1 : current amplitude offset state from owned pop
    // 2 : current amplitude direction
    // 3 : Satisfactory termination counter of owned pop
    int att_zigzag_noise_pop[CHAR_AMOUNT_PER_LINE][4] = { };

    bool att_zigzag_isWithinRange(int index, int offset) {
        return att_zigzag_noise_pop[index][0] == 1
            && att_zigzag_global_offset == offset;
    }

    NoiseAttribute noise_zigzag(Flavour &flavour, int x, int y) {

        if(att_zigzag_current_y != y) {
            att_zigzag_current_y = y;

            att_zigzag_global_direction =
                    ( att_zigzag_global_offset == att_zigzag_amp) * -2
                    + att_zigzag_global_direction
                    + (2 * (att_zigzag_global_offset == -att_zigzag_amp) );
            att_zigzag_global_offset += att_zigzag_global_direction;

            att_zigzag_noise_pop[(int)random()%CHAR_AMOUNT_PER_LINE][0] = 1;
        }

        int index = x % CHAR_AMOUNT_PER_LINE;

        if(att_zigzag_isWithinRange(index, 0) ||
            att_zigzag_isWithinRange((index+1) % CHAR_AMOUNT_PER_LINE, -1) ||
            att_zigzag_isWithinRange((index+2) % CHAR_AMOUNT_PER_LINE, -2) ||
            att_zigzag_isWithinRange((index+3) % CHAR_AMOUNT_PER_LINE, -3) ||
            att_zigzag_isWithinRange((index+4) % CHAR_AMOUNT_PER_LINE, -4) ||
            att_zigzag_isWithinRange(((index-1<0)*CHAR_AMOUNT_PER_LINE)+index-1, 1) ||
            att_zigzag_isWithinRange(((index-2<0)*CHAR_AMOUNT_PER_LINE)+index-2, 2) ||
            att_zigzag_isWithinRange(((index-3<0)*CHAR_AMOUNT_PER_LINE)+index-3, 3) ||
            att_zigzag_isWithinRange(((index-4<0)*CHAR_AMOUNT_PER_LINE)+index-4, 4))
        {
            return flavour.generateNoise(x, y);
        } else {
            return 0.0;
        }
    }

    NoiseAttribute noise_zigzag_legacy(Flavour &flavour, int x, int y) {
        if(att_zigzag_current_y != y) {
            att_zigzag_current_y = y;

            for(int i=0; i < CHAR_AMOUNT_PER_LINE; i++) {
                att_zigzag_noise_pop[i][2] =
                        ((att_zigzag_noise_pop[i][1] == att_zigzag_amp) * -2)
                        + (att_zigzag_noise_pop[i][2] * (att_zigzag_noise_pop[i][3]<SATISFACTION_LIMIT))
                        + (2 * (att_zigzag_noise_pop[i][1] == -att_zigzag_amp));

                att_zigzag_noise_pop[i][1] += att_zigzag_noise_pop[i][2];
                att_zigzag_noise_pop[i][3] += (att_zigzag_noise_pop[i][0] == 1 && att_zigzag_noise_pop[i][3]<SATISFACTION_LIMIT)*1;
            }

            int newPopIndex = (int)random()%CHAR_AMOUNT_PER_LINE;

            bool isInit = att_zigzag_noise_pop[newPopIndex][0] == 1;

            att_zigzag_noise_pop[newPopIndex][1] = isInit * att_zigzag_noise_pop[newPopIndex][1];
            att_zigzag_noise_pop[newPopIndex][2] =
                    isInit * att_zigzag_noise_pop[newPopIndex][2]
                    +
                    (!isInit) * ((newPopIndex%2 == 0) * -2 + 1);
            att_zigzag_noise_pop[newPopIndex][0] = 1;
        }

        int index = x % CHAR_AMOUNT_PER_LINE;

        if((att_zigzag_noise_pop[index][0] == 1 && att_zigzag_noise_pop[index][1] == 0) ||
           (att_zigzag_noise_pop[(index+1) % CHAR_AMOUNT_PER_LINE][0] == 1 && att_zigzag_noise_pop[index+1][1] == -1 ) ||
           (att_zigzag_noise_pop[(index+2) % CHAR_AMOUNT_PER_LINE][0] == 1 && att_zigzag_noise_pop[index+2][1] == -2 ) ||
           (att_zigzag_noise_pop[(index+3) % CHAR_AMOUNT_PER_LINE][0] == 1 && att_zigzag_noise_pop[index+3][1] == -3 ) ||
           (att_zigzag_noise_pop[(index+4) % CHAR_AMOUNT_PER_LINE][0] == 1 && att_zigzag_noise_pop[index+4][1] == -4 ) ||
           (att_zigzag_noise_pop[((index-1<0)*CHAR_AMOUNT_PER_LINE)+index-1][0] == 1 && att_zigzag_noise_pop[((index-1<0)*CHAR_AMOUNT_PER_LINE)+index-1][1] == 1 ) ||
           (att_zigzag_noise_pop[((index-2<0)*CHAR_AMOUNT_PER_LINE)+index-2][0] == 1 && att_zigzag_noise_pop[((index-2<0)*CHAR_AMOUNT_PER_LINE)+index-2][1] == 2 ) ||
           (att_zigzag_noise_pop[((index-3<0)*CHAR_AMOUNT_PER_LINE)+index-3][0] == 1 && att_zigzag_noise_pop[((index-3<0)*CHAR_AMOUNT_PER_LINE)+index-3][1] == 3 ) ||
           (att_zigzag_noise_pop[((index-4<0)*CHAR_AMOUNT_PER_LINE)+index-4][0] == 1 && att_zigzag_noise_pop[((index-4<0)*CHAR_AMOUNT_PER_LINE)+index-4][1] == 4 ))
        {
            return flavour.generateNoise(x, y);
        } else {
            return 0.0;
        }
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
