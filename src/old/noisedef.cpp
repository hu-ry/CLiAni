//##############################################################################
//## Project: ClAni ########################### Created by hury on 22.04.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

//#include <stdexcept>
//#include <noisedef.h>


template <class T>
void CharIteration<T>::prepareGradient(int seed) {
    generate_gradients(_Gradients, _GradSize, seed);
    setup_prep++;
}

template <class T>
void CharIteration<T>::setVariety (const T *var, const float range[NOISE_SYMBOL_VARIETY]) {
    for(int i=0; i<NOISE_SYMBOL_VARIETY; i++) {
        _uniqueSymbols[i] = var[i];
        _symbolRanges[i] = range[i];
    }
    setup_prep++;
}

template <class T>
T* CharIteration<T>::runRow() {
    if(setup_prep != 2) {
        return nullptr;
    }
    T result[size];

    for(int i=0; i<size; i++) {
        double noise = genPerlinNoise(i, _currentRow, _Gradients);

        for(int k=0; k<NOISE_SYMBOL_VARIETY; k++) {
            if(noise < _symbolRanges[k]) {
                result[i] = _uniqueSymbols[k];
                symbols[i] = _uniqueSymbols[k];
            }
        }
    }

    _currentRow = (_currentRow+1)%NOISE_HEIGHT;
    return result;
}

template <class T>
void CharIteration<T>::addToTop (T const& elem) {
    if(currentSize < size) {
        symbols[currentSize] = elem;
        currentSize++;
    } else {
        throw std::out_of_range("CharIteration<>::add(): Array is full");
    }
}

template <class T>
void CharIteration<T>::remove () {
    if (currentSize == 0) {
        throw std::out_of_range("CharIteration<>::remove(): empty array");
    }
    currentSize -= 1;
    symbols[currentSize] = nullptr;
}

template <class T>
T CharIteration<T>::top () const {
    if (currentSize == 0) {
        throw std::out_of_range("CharIteration<>::top(): empty array");
    }

    // return last element
    return symbols[currentSize-1];
}

template <class T>
T* CharIteration<T>::getptr () const {
    return symbols;
}