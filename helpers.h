#ifndef HELPERS_H
#define HELPERS_H

#include "dataStructures.h"

void seedRand(void);

int generateId(void);

void copy_array(const void *source, void *destination, int element_size, int n);

void merge(delivery** arr, int l, int m, int r);

void mergeSort(delivery** arr, int l, int r);

#endif
