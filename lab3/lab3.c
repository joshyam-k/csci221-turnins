#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lab3.h"

void add_to_end(linklist a, uint32_t val) {
    /*initialize a pointer that points at the first node in our linked list */
    node_l * current = a.head;
    /*recall this is just *(current.next) != NULL */
    /*so we dereference current.next and check if it is equal to NULL which would indicate the end of the linked list*/
    /*if we are not at the end of the linked list we set current to point to the link to the next node*/
    while(current->next != NULL){
        current = current->next;
    }
    /*once the above code terminates we know that we are at the last node in our linked list*/
    /* we allocate space for the node we are going to add*/
    current->next = (node_l *)malloc(sizeof(node_l));
    /*we then set the value to the function input and set the node to point to NULL */
    current->next->val = val;
    current->next->next = NULL;
}

linklist* create_ll(uint32_t val, int size){
    /*make use of add_to_end() to populate the linked list*/
    /*to start we have to intialize the linked list*/
    linklist llist;
    llist.head = NULL;
    llist.head = (node_l *) malloc(sizeof(node_l));
    llist.head->val = val;
    llist.head->next = NULL;
    for(int i; i < size; i++){
        add_to_end(llist, val);
    }

    linklist* ll_p = &llist;
    return ll_p;
}


int* odd_rm(int* array, int size, int n_even){
    int* ret = malloc(n_even*sizeof(int32_t));
    for(int i; i < size; i++){
        if(array[i] % 2 == 0){
            ret[i] = array[i];
        }
    }
    return ret;
}


void test(int* arr, int size){
    for(int i; i < size; i++){
        printf("item i is %d\n", arr[i]);
    }
}

int main(){
    int A[3] = {1,2,3};
    int* pA = A;
    test(pA, 3);
    return 0;
}













