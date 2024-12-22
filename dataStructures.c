#include "dataStructures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

customer* newCustomer(customer* head, const char* name, const char* surname, char* city, int id){

    customer* node = (customer*) malloc(sizeof(customer));

    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL; // Exit the function if allocation fails
    }

    node->id = id;
    strcpy(node->name,name);
    strcpy(node->surname,surname);
    strcpy(node->city,city);

    if(head != NULL){

        node->next = head;

    }else{

        node->next = NULL;
    }

    return node;

}

void printAllCustomers(customer* head) {
    while (head != NULL) {
        printf("%s %s, city: %s, id: %d\n", head->name, head->surname, head->city, head->id);
        head = head->next;
    }
}

void freeCustomers(customer* head) {
    customer* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
