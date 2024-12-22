#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct customerNode{

    struct customerNode* next;
    int id;
    char name[20];
    char surname[20];
    char city[20];

    //stack *history;


}   customer;

customer* newCustomer(customer* head, const char* name, const char* surname, char* city, int id);

void printAllCustomers(customer* head);

void freeCustomers(customer* head);


#endif // DATASTRUCTURES_H
