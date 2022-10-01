#include <stdint.h>

typedef struct NODE {
    int32_t val;
    struct NODE *left, *right;
} node;

typedef struct BST {
    node* head;
    int length;
} bst;
