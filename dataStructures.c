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

//Functions related to cities tree

city* newCity(char name[],city* parent){

    city* newNode = malloc(sizeof(city));

    strcpy(newNode->name,name);
    newNode->childrenCount = 0;

    if(parent == NULL){

        newNode->parent = NULL;
        newNode->depth = 0;

    }else{

        newNode->parent = parent;
        newNode->depth = parent->depth + 1;
        parent->children[parent->childrenCount] = newNode;
        parent->childrenCount++;

    }

    return newNode;

}

void printAllCities(city* root){

    if(root == NULL){

        return;

    }else{

        int i = 0;

        while(i<root->depth){

            printf("-");

            i++;

        }
        printf("%s\n",root->name);

        i = 0;

        while(i<root->childrenCount){

            printAllCities(root->children[i]);

            i++;

        }

    }
}

void freeCities(city* root){

    if(root == NULL){

        return;

    }else{

        int i = 0;

        while(i<root->childrenCount){

            freeCities(root->children[i]);

            i++;

        }

        free(root);

    }
}

city* createCityTree(){

    city* buenosAires = newCity("Buenos Aires",NULL);

        city* laPlata = newCity("La Plata",buenosAires);

        city* rosario = newCity("Rosario",buenosAires);

            city* corrientes = newCity("Corrientes",rosario);

            city* santaFe = newCity("Santa Fe",rosario);

            city* cordoba = newCity("Cordoba",rosario);

                city* mendoza = newCity("Mendoza",cordoba);

        city* marDelPlata = newCity("Mar del Plata",buenosAires);

            city* bahiaBlanca = newCity("Bahia Blanca",marDelPlata);

                city* neuquen = newCity("Neuquen",bahiaBlanca);

                    city* bariloche = newCity("Bariloche",neuquen);

                    city* ushuaia = newCity("Ushuaia",neuquen);

    printAllCities(buenosAires);

    return buenosAires;


}

city* findCityNode(city* root, char name[]){

    if(root == NULL){

        printf("Received null as a root!!\n");

        return NULL;

    }else{

        if(strcmp(root->name,name) == 0){

        return root;

        }

        int i = 0;

        while(i<root->childrenCount){

            city* found = findCityNode(root->children[i],name);

            if(found != NULL){

            return found;

            }

            i++;

        }

    }

    return NULL;
}

int calculateDistance(city* root, char name1[], char name2[]){

    if(root == NULL){

        return -1;

    }

    city* node1 = findCityNode(root,name1);

    city* node2 = findCityNode(root,name2);

    if(node1 == NULL || node2 == NULL){

        printf("One of the two cities does not exist in the route tree\n");
        return -1;

    }

    int d1 = node1->depth;
    int d2 = node2->depth;

    while(node1->depth > node2->depth){

        node1 = node1->parent;

    }

    while(node2->depth > node1->depth){

        node2 = node2->parent;

    }

    while(node1 != node2){

        node1 = node1->parent;
        node2 = node2->parent;

    }

    int lcadepth = node1->depth;

    return (d1+d2 - 2*lcadepth);

}
