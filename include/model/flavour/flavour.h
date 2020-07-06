//##############################################################################
//## Project: ClAni ########################### Created by hury on 01.05.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################


#ifndef CLIANIMATION_FLAVOUR_H
#define CLIANIMATION_FLAVOUR_H


#include <cstdint>

namespace tasty {

/**
 * Defines a 2-dimensional vector
 * @c X_AXIS is for the value of x double
 * @c Y_AXIS is for the value of y double
 */
    typedef struct {
        double x;
        double y;
    } Vec2D;

/**
 * Defines a 2-dimensional vector
 * @c X_AXIS is for the value of x uint32
 * @c Y_AXIS is for the value of y uint32
 */
    typedef struct {
        uint32_t x;
        uint32_t y;
    } Vec2UI;

    typedef struct {
        double tl;
        double tr;
        double bl;
        double br;
    } GridRectangle;

    enum Effect {
        ScrollEffect = 1,
        RainEffect,
        JiggleEffect
    };

/**
 * Flavour describes the types of different noise algorithms that can be
 * implemented by inheriting from it. Its supposed to be an empty superclass
 * which gets its functionality by subclasses.
 */
    class Flavour {
    public:

        //virtual Flavour() = default;
        virtual ~Flavour() = default;

        /**
         * Generates a noise-value for the specified coordinates within the range of
         * 0.0f - 1.0f.
         * @param x : signed integer 32-bit
         * @param y : signed integer 32-bit
         * @return floating point number with double precision between 0.0f - 1.0f
         */
        virtual double generateNoise(int x, int y) {
            return -1;
        }

    private:


    };
}; // end of namespace tasty
#endif //CLIANIMATION_FLAVOUR_H
