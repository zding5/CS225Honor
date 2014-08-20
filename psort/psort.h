/**
 * @file psort.h
 */

#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>
#include <math.h>

using namespace std;
using std::vector;

namespace ParallelSort
{
    /**
     * Public wrapper for the parallel sort implementation.
     * @param array The structure to sort
     */
    template <class T>
    void psort(vector<T>* array);

    template <typename T>
    void psort(vector<T> & array);

    template <typename T>
    void modified_quicksort(vector<T> &array, int head, int tail);

    // template <typename T>
    // void insertionsort(vector<T> &array, int h, int t);

    template <typename T>
    void insertionsort(vector<T> &array, int head, int tail);

    template <typename T>
    int median(vector<T> &array, int a, int b, int c);

    template <typename T>
    void swap(vector<T> &array, int a, int b);

    template <typename T>
    void groupswap(vector<T> &array, int a, int b, int c);

    template <typename T>
    void unbalancedmerge(vector<T> & array, int l, int m, int r);

    template <typename T>
    void balancedmerge(vector<T> & array, int l, int m, int r);

    template <typename T>
    void merge(vector<T> & array, int l, int m, int r);

    template <typename T>
    void Sorter(vector<T> & array);

    // template <typename T>

    // template <typename T>

    // template <typename T>

    // template <typename T>

    // template <typename T>






    /**
     * TODO: add helper functions here.
     * Note: you can also add additional classes and/or files.
     * Make sure you follow the instructions in the Makefile.
     */

}

#include "psort.cpp"
#endif
