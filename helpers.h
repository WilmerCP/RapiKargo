#ifndef HELPERS_H
#define HELPERS_H

#include "dataStructures.h"

void seedRand(void);

int generateId(void);

void copy_array(const void *source, void *destination, int element_size, int n);

void merge(delivery** arr, int l, int m, int r);

void mergeSort(delivery** arr, int l, int r);

delivery** joinArrays(delivery** arr1, int size1, delivery** arr2, int size2);

void removeFromList(sortedList* li, int index);

void printAllCargos(sortedList* li);

void printArray(delivery** arr,int n);

delivery* binarySearch(delivery** arr, int low, int high, int id);

#endif
