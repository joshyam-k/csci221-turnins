#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lab3.h"

void add_to_end(linkedlist a, uint32_t val) {
    /*initialize a pointer that points at the first node in our linked list */
    node* current = a.head;
    /*recall this is just *(current.next) != NULL */
    /*so we dereference current.next and check if it is equal to NULL which would indicate the end of the linked list*/
    /*if we are not at the end of the linked list we set current to point to the link to the next node*/
    while(current->next != NULL){
        current = current->next;
    }
    /*once the above code terminates we know that current is at the last node in our linked list*/
    /* we allocate space for the node we are going to add*/
    current->next = (node*)malloc(sizeof(node));
    /*we then set the value to the function input and set the node to point to NULL */
    current->next->val = val;
    current->next->next = NULL;
}

linkedlist* create_ll(uint32_t val, int size){
    /*make use of add_to_end() to populate the linked list*/
    /*to start we have to intialize the linked list*/
    linkedlist llist;
    llist.head = NULL;
    llist.head = (node*) malloc(sizeof(node));
    llist.head->val = val;
    llist.head->next = NULL;
    /*using size - 1 because we initialized the linked list using the value*/
    for(int i = 0; i < (size - 1); i++){
        add_to_end(llist, val);
    }

    linkedlist* ll_p = &llist;
    return ll_p;
}


void ll_val_remove(linkedlist a, int valrm){
    /* still to do */
}

void free_ll(linkedlist* pLL){
    /*intitialize a node*/
    node* current;
    /*while *(pLL).head != NULL we... */
    while(pLL->head != NULL){
        /*set current to point at the same thing as the head node */
        current = pLL->head;
        /*set the headnode in the linked list equal to the next node in the linked list*/
        pLL->head = pLL->head->next;
        /*remove the node that was not the end of the linked list*/
        free(current);
    }
}


void print_ll(linkedlist a){
    node* current = a.head;

    while(current != NULL){
        printf("%d\n", current->val);
        current = current->next;
    }
}


int main(){
    linkedlist ll;
    ll.head = NULL;
    ll.head = (node*) malloc(sizeof(node));
    ll.head->val = 1;
    ll.head->next = NULL;
    
    linkedlist* a = create_ll(10, 4);
    print_ll(*a);
    free_ll(a);
    return 0;
}













