//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <model/greasemonkey.h>

namespace CliAniHury {

    GreaseMonkey::GreaseMonkey() {
        _inputCharSize = MAX_INPUT_CHAR;
        _inputChars.resize(_inputCharSize);
        _usedFlavour = new tasty::Flavour;
    }

    GreaseMonkey::~GreaseMonkey() {
        delete _usedFlavour;
    }

    void GreaseMonkey::setup(int seed, int flavour, int attribute) {
        delete _usedFlavour;

        switch(flavour) {
            case FLAVOUR_PERLIN:
                _usedFlavour = new tasty::PerlinNoise(seed);
                break;
            case FLAVOUR_VORONOI:
                _usedFlavour = new tasty::Voronoi(seed);
                break;
            case FLAVOUR_CELLULAR:
                _usedFlavour = new tasty::Cellular(seed);
                break;
            case FLAVOUR_TYPE_1:
                _usedFlavour = new tasty::Flavour();
                break;
            default:
                _usedFlavour = new tasty::Flavour();
        }

        switch(attribute) {
            case ATTRIBUTE_SCROLLING:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_scrolling);
                break;
            case ATTRIBUTE_RAINING:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_raining);
                break;
            case ATTRIBUTE_ZIGZAG:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_zigzag);
                break;
            case ATTRIBUTE_ZIGZAG_LEGACY:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_zigzag_legacy);
                break;
            case ATTRIBUTE_STATIC:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_static);
                break;
            default:
                _currIteration.assignFlavour(_usedFlavour, &tasty::noise_scrolling);
        }

        _currIteration.setVariety(_inputChars, _ranges);
    }

    const char* GreaseMonkey::runIteration() {
        return _currIteration.runRow();
    }

    void GreaseMonkey::setCharacters(const char *addChars, int amount) {
        if(amount > MAX_INPUT_CHAR) {
            amount = MAX_INPUT_CHAR;
        }
        _inputCharSize = amount;
        for (int i = 0; i < amount; i++) {
            _inputChars[i] = addChars[i];
        }

    }

}; // end of namespace CliAniHury