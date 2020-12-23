//##############################################################################
//## Project: ClAni ########################### Created by hury on 17.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#include <greasemonkey.h>
#include <utilz/global.h>

#include <model/flavour/perlinnoise.h>
#include <model/flavour/voronoi.h>
#include <model/flavour/cellular.h>

namespace CliAniHury {

    GreaseMonkey::GreaseMonkey() {
        _inputCharSize = MAX_INPUT_CHAR;
        _inputChars.resize(_inputCharSize);
        _usedFlavour = new tasty::Flavour;
    }

    GreaseMonkey::~GreaseMonkey() {
        delete _usedFlavour;
    }

    void GreaseMonkey::setup(int opm, int seed, selection taste) {

        if(opm == 1) {
            initFlavour(taste.option_s.taste, taste.option_s.effect, seed);
        } else {

        }

    }

    const char* GreaseMonkey::runIteration() {
        return _currIteration.runRow();
    }

    const char* GreaseMonkey::runFrame() {
        // TODO: Give this something to output!
        return nullptr;
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

    void GreaseMonkey::initFlavour(int flavour, int attribute, int seed) {
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

    void GreaseMonkey::initScene(int scene, int effect, int seed) {

    }

}; // end of namespace CliAniHury