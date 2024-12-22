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

typedef struct cityNode{

    struct cityNode* parent;
    struct cityNode* children[3];
    int depth;
    char name[20];
    int childrenCount;


} city;

city* newCity(char name[],city* parent);
void printAllCities(city* root);
void freeCities(city* root);
city* createCityTree();
city* findCityNode(city* root, char name[]);
int calculateDistance(city* root, char name1[], char name2[]);

#endif // DATASTRUCTURES_H
