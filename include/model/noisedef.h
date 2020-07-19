//##############################################################################
//## Project: ClAni ########################### Created by hury on 19.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_NOISEDEF_H
#define CLIANIMATION_NOISEDEF_H

#include <stdexcept>
#include <memory>
#include <utilz/global.h>
#include <model/flavour/flavour.h>

#define CHAR_AMOUNT_PER_LINE WINDOW_LINE_WIDTH
#define CHAR_REPEAT_HEIGHT 256

#define SYMBOL_VARIETY 10

namespace tasty {

    typedef double NoiseAttribute;

    NoiseAttribute noise_scrolling(Flavour &flavour, int x, int y);
    NoiseAttribute noise_raining(Flavour &flavour, int x, int y);
    NoiseAttribute noise_zigzag(Flavour &flavour, int x, int y);
    NoiseAttribute noise_zigzag_legacy(Flavour &flavour, int x, int y);
    NoiseAttribute noise_static(Flavour &flavour, int x, int y);

    typedef NoiseAttribute (*noise_attribute_func) (Flavour &, int, int);



    /**
     * Enables Clani a per line output mode of characters in form of for example
     * a scrolling image with different kind of effects applied on them.
     * For proper initialization after constructor invocation setVariety() and
     * assignFlavour() should be called for desired properties of output.
     *
     * @remark Its recommended to not set t_size higher than the maximum width
     *         of the used flavour full grid width(128 normally).
     */
    class CharIteration {
    private:
        std::string _symbols; // elements
        Flavour *_entity = nullptr;
        noise_attribute_func _TypeFunc = nullptr;
        int _size; // size of allocation
        int _currentRow = 0; // current iteration row

        int setup_prep = 0; // flag for indicating if setup ran

        std::string _uniqueSymbols;
        float *_symbolRanges;


    public:
        explicit CharIteration(unsigned int t_size) {
            _size = (int)t_size;

            _symbols.resize(_size);
            _uniqueSymbols.resize(SYMBOL_VARIETY);
            _symbolRanges = new float[SYMBOL_VARIETY];
        }

        ~CharIteration() {
            delete _symbolRanges;
        }

        /**
         * Uses the given Flavour reference to generate Patterns in the future.
         * @param entity : Flavour of noise algorithm to be used
         */
        void assignFlavour(Flavour *entity, noise_attribute_func attribute) {
            _entity = entity;
            _TypeFunc = attribute;
        }

        /**
         * Sets the to be used char-characters for output on command line.
         */
        void setVariety(std::string var, const float *range) {
            for (int i = 0; i < SYMBOL_VARIETY; i++) {
                _uniqueSymbols[i] = var[i];
                _symbolRanges[i] = range[i];
            }
            setup_prep++;
        }

        /**
         * Calculates a row of noise via generateNoise() and translates values into
         * char's for output on command line.
         * @return array of read-only char
         */
        const char *runRow() {
            if (setup_prep != 1) {
                return nullptr;
            }

            for (int i = 0; i < _size; i++) {

                double noise = (*_TypeFunc)(*_entity, i, _currentRow);
                bool notfound = true;
                for (int k = 0; k < SYMBOL_VARIETY && notfound; k++) {
                    // To prevent the compiler from skipping iterations when
                    // using -O3 and causing unwanted behaviour
                    notfound = noise >= _symbolRanges[k];
                    _symbols[i] = (!notfound) * _uniqueSymbols[k];
                }
            }

            _currentRow = (1 + _currentRow) % CHAR_REPEAT_HEIGHT;
            //_currentRow = _currentRow == 0 ? CHAR_REPEAT_HEIGHT : _currentRow-1;
            return _symbols.c_str();
        }
        // TODO: Maybe add as feature OpenMP usage for Flavour generation and memory
        //       allocation for generated data to avoid calculating redundant data.

        /**
         * Returns the address to the read-only char array, that is used to save the
         * char's for every iteration.
         * @return address to read-only char array
         */
        const char *getptr() const {
            return _symbols.c_str();
        }

        /**
         * Returns the size of allocated char memory
         * @return size of allocated char memory
         */
        int getSize() {
            return _size;
        }
    };

}; // end of namespace tasty
#endif //CLIANIMATION_NOISEDEF_H
