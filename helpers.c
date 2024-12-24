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

    free(R);
    free(L);
}

void mergeSort(delivery** arr, int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

delivery** joinArrays(delivery** arr1, int size1, delivery** arr2, int size2){

    int newSize = size1+size2;

    delivery** joinedArray = (delivery**) malloc(sizeof(delivery*)*newSize);

    int i;

    for(i=0;i<size1;i++){

        joinedArray[i] = arr1[i];

    }

    int j = size1;

    for(i=0;i<size2;i++){

        joinedArray[j] = arr2[i];
        j++;

    }

    return joinedArray;

}

void removeFromList(sortedList* li, int index) {
    // Check if the index is within bounds
    if (index >= li->items) {
        printf("Index out of bounds\n");
        return;
    }

    for (int i = index; i < (li->items - 1); i++) {
        li->arr[i] = li->arr[i + 1];
    }

    li->items--;
}

void printAllCargos(sortedList* li){

    printf("Number of items of the list: %d\n",li->items);
    printf("Capacity of the list: %d\n",li->capacity);
    int i;

    for(i=0; i<li->items;i++){

    printf("%s\n",li->arr[i]->description);

    }

}

void printArray(delivery** arr,int n){

    int i;

    for(i=0; i<n;i++){

    printf("%s\n",arr[i]->description);

    }

}

delivery* binarySearch(delivery** arr, int low, int high, int id)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid]->id == id)
            return arr[mid];

        // If x greater, ignore left half
        if (arr[mid]->id < id)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return NULL;
}
