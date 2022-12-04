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


int ll_val_remove(linkedlist a, int valrm){
    int total_removed = 0;
    node* current = a.head;
    while(current->next != NULL){;
        // steps
        // check if current->next->value is valrm
        // if so make a temporary pointer to current->next 
        // then change current->next to current->next->next and then free the temporary pointert
        if (current->next->val == valrm){
            node* to_del = current->next;
            current->next = current->next->next;
            free(to_del);
            total_removed++;
        } else {
            current = current->next;
        }
    }
    return total_removed;
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

// helper function to visualize if linked list functions are working
void print_ll(linkedlist a){
    node* current = a.head;
    while(current != NULL){
        printf("%d\n", current->val);
        current = current->next;
    }
}

int* odds_remove(int* arr, int arr_size, int n_even){
    /*allocate memory for the array that we will return */
    int* ret = malloc(n_even * sizeof(int32_t));
    int even = n_even;
    int i = 0;
    for (i = 0, even = 0; i < arr_size; i++){
        if(arr[i] % 2 == 0){
            ret[even++] = arr[i];
        }
    }
    return ret;
}

char* find_char(char* string, char c){
    while(*string != '\0'){
        if(*string == c){
            return string;
        }
        string++;
    }
    char null_c[] = "\0";
    string = null_c;
    return string;
}

char* copy_char(char* string, int len){
    char* copy = malloc((len + 1)*sizeof(char));
    for(int i = 0; i < (len + 1); i++){
        copy[i] = string[i];
    }
    return copy;
}  


int main(){
    /*
    node* header = NULL;
    node* second = NULL;
    node* third = NULL;
    node* fourth = NULL;

    header = (node*)malloc(sizeof(node));
    second = (node*)malloc(sizeof(node));
    third = (node*)malloc(sizeof(node));
    fourth = (node*)malloc(sizeof(node));

    header->val = 1;
    header->next = second;
    second->val = 2;
    second->next = third;
    third->val = 2;
    third->next = fourth;
    fourth->val = 4;
    fourth->next = NULL;

    linkedlist ll;
    ll.head = NULL;
    ll.head = (node*)malloc(sizeof(node));
    ll.head = header;
    
    int ret = ll_val_remove(ll, 2);
    printf("occurences = %d\n", ret); 
    print_ll(ll);
    */
    linkedlist* a = create_ll(10, 4);
    print_ll(*a);
    free_ll(a);
    int b[8] = {1,2,3,4,5,6,8,20};
    int* b_ret = odds_remove(b, 8, 5);
    for(int i = 0; i < 5; i++){
        printf("item i is %d\n", b_ret[i]);
    }
    char* s = "hello";
    char let = 'e';
    char* ret_s = find_char(s, let);
    char* ret_s2 = copy_char(s, 6);
    printf("first instance of %c gives us %s\n", let, ret_s);
    printf("if we copy %s we get %s\n", s, ret_s2);
    free(ret_s2);
    return 0;
}













