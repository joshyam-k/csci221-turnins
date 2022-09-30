#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lab3.h"

void add_to_end(linklist a, uint32_t val) {
    node_l * current = a.head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = (node_l *)malloc(sizeof(node_l));
    current->next->val = val;
    current->next->next = NULL;

}



int main(){
    /*a consists of a pointer called head to a node and an integer size*/
    linklist a;
    /*we start by setting the head pointer equal to NULL */
    a.head = NULL;
    /* we then allocate memory on the heap */
    a.head = (node_l *) malloc(sizeof(node_l));
    a.head->val = 1;
    a.head->next = NULL;
    return 0;
}
