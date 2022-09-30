#include <stdint.h>

typedef struct node {
    uint32_t val;
    struct node* next;
} node_l;


typedef struct linkedlist {
    node_l* head;
    int size;
} linklist;
