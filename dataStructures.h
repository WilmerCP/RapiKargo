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

customer* findCustomer(customer* head, int id);

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

typedef enum {

    PROCESSING,
    ON_THE_WAY,
    DELIVERED

} DeliveryState;

typedef struct delivery {

    int distance;
    char description[50];
    int id;
    int customerId;
    char from[20];
    char to[20];
    DeliveryState state;

} delivery;

typedef struct priorityQueue{

    delivery** heap;
    int capacity;
    int items;

} priorityQueue;

priorityQueue* createNewQueue(int capacity);

delivery* createNewDelivery(int distance, char from[],char to[],int customerId, int id,const char description[]);

void enqueueDelivery(priorityQueue* pq, delivery* element);

delivery* dequeueDelivery(priorityQueue* pq);

void freeQueue(priorityQueue* pq);

char* get_delivery_state_name(DeliveryState state);

#endif // DATASTRUCTURES_H
