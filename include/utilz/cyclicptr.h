//##############################################################################
//## Project: ClAni ########################### Created by hury on 05.07.2020 ##
//##############################################################################
//## Author: Ryan Huth(hury) ############################# License: GNU GPLv3 ##
//##############################################################################

#ifndef CLIANIMATION_CYCLICPTR_H
#define CLIANIMATION_CYCLICPTR_H

#include <iterator>

namespace CliAniHury {

    template<class T>
    class CyclicPtr {
    private:
        T *_entity = nullptr; // raw pointer to internal array
        unsigned int _size = 0; // size of allocation
        unsigned int _current = 0; // current ptr offset !UNUSED!

        unsigned int _ByteSize = sizeof(T); // returns size of _entity in bytes

    public:
        /**
         * Creates a CyclicPtr object.
         * Allocates an empty array of given size.
         *
         * @param t_size : unsigned int of array size to be allocated
         */
        explicit CyclicPtr(unsigned int t_size) {
            _size = t_size;
            _entity = new T[t_size];
            _ByteSize = sizeof(T) * t_size;
        }


        /**
         * Copies the array given array in newly allocated memory
         *
         * @param t_size : unsigned int of given array size
         * @param t_array : ptr of array to copy
         */
        explicit CyclicPtr(unsigned int t_size, T *t_array) {
            _size = t_size;
            _entity = new T[t_size];
            // copy array into allocated memory
            std::copy(t_array, t_array+t_size, _entity);
            _ByteSize = sizeof(T) * t_size;
        }

        ~CyclicPtr() {
            delete[]_entity;
        }

        /**
         * Returns the element at given index with cyclic overflow protection.
         *
         * @param pos : int index to access array
         * @return Write protected reference of requested element
         */
        T& at(int pos) const;

        /**
         * Takes pointer to an array and its size for copying into cyclicptr.
         * @c WARNING: Must not be bigger than already allocated array from
         * object initialization.
         *
         * @param array : T pointer to array
         * @param size : int size of given array
         */
        void copy(T* array, int size);

        /**
         * Returns a pointer to the array, which allows for writing on it.
         *
         * @return pointer to the object
         */
        T* getptr();
    };

    template<class T>
    T& CyclicPtr<T>::at(int pos) const {
        if(pos < 0) {
            return _entity[((int)_size+pos)%(int)_size];
        }
        if(pos >= (int)_size) {
            return _entity[pos%(int)_size];
        }
        return _entity[pos];
    }

    template<class T>
    void CyclicPtr<T>::copy(T* array, int size) {
        std::copy(array, array+size, _entity);
    }

    template<class T>
    T* CyclicPtr<T>::getptr() {
        return _entity;
    }


}; // end of namespace CliAniHury

#endif //CLIANIMATION_CYCLICPTR_H
