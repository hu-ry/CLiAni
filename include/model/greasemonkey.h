//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_GREASEMONKEY_H
#define CLIANIMATION_GREASEMONKEY_H

#include <model/noisedef.h>
#include <model/framedef.h>
#include <model/flavour/flavour.h>

#define MAX_INPUT_CHAR SYMBOL_VARIETY

namespace CliAniHury {


    class GreaseMonkey {
    public:
        GreaseMonkey();

        ~GreaseMonkey();

        void setup(int opm, int seed, selection taste);
        const char* runIteration();
        const char* runFrame();

        void setCharacters(const char *addChars, int amount);

    private:
        tasty::Flavour* _usedFlavour;
        tasty::CharIteration _currIteration = tasty::CharIteration(CHAR_AMOUNT_PER_LINE);

        std::string _inputChars;
        unsigned int _inputCharSize;

        float _ranges[MAX_INPUT_CHAR] = {0.1, 0.2, 0.3, 0.38,
                           0.47, 0.56, 0.64, 0.71, 0.83, 999.0};

        void initFlavour(int flavour, int attribute, int seed);
        void initScene(int scene, int effect, int seed);
    };

}; // end of namespace CliAniHury

#endif //CLIANIMATION_GREASEMONKEY_H
