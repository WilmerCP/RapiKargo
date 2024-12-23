#include "helpers.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "dataStructures.h"

void seedRand(){

    srand(time(NULL));

}

//Returns a 9 digit numeric ID
int generateId(){

    int id = 0, i = 0;

    for(i = 0; i<9;i++){

        if(i == 0){

            id += (rand() % 9) + 1;

        }else{

            id = id*10 + rand() % 10;

        }

    }

    //printf("Generated a 9 digit ID: %d \n",id);

    return id;

}
//Makes a copy of an array
void copy_array(const void *source, void *destination, int element_size, int n) {

    memcpy(destination, source, element_size * n);
}

void merge(delivery** arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    delivery** L = (delivery**) malloc(sizeof(delivery*)*n1);
    delivery** R = (delivery**) malloc(sizeof(delivery*)*n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i]->distance <= R[j]->distance) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(delivery** arr, int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
