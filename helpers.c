#include "helpers.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
