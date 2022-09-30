#include <stdint.h>

typedef struct NODE {
    uint32_t val;
    struct NODE* next;
} node;


typedef struct LINKEDLIST {
    node* head;
    int size;
} linkedlist;
