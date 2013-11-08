//
//  DynamicArray.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DynamicArray.h"

template <class T> DynamicArray<T>::DynamicArray() {
    numData = 0;
    arraySize = 4;
    data = new T[arraySize];
}

template <class T> DynamicArray<T>::DynamicArray(int a) {
    numData = 0;
    arraySize = a;
    data = new T[arraySize];
}

template <class T> DynamicArray<T>::~DynamicArray() {
    numData = 0;
    delete [] data;
}

template <class T> bool DynamicArray<T>::append(T item) {
    if (numData == arraySize) {
        arraySize *=2;
        T *temp = data;
        if (!(data = new T[arraySize])) return false;
        for (int i = 0; i < numData; i++) {
            data[i] = temp[i];
        }
        delete [] temp;
    }
    data[numData++] = item;
    return true;
}

template <class T> bool DynamicArray<T>::truncate() {
    if (numData != arraySize) {
        T *temp = data;
        arraySize = numData;
        if (!(data = new T[arraySize])) return false;
        for (int i = 0; i < numData; i++) {
            data[i] = temp[i];
        }
        delete [] temp;
    }
    return true;
}