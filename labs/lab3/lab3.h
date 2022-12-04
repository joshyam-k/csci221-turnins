#include <stdint.h>

typedef struct NODE {
    uint32_t val;
    struct NODE* next;
} node;


typedef struct LINKEDLIST {
    node* head;
    int size;
} linkedlist;


void add_to_end(linkedlist a, uint32_t val);
linkedlist* create_ll(uint32_t val, int size);
int ll_val_remove(linkedlist a, int valrm);
void free_ll(linkedlist* pLL);
void print_ll(linkedlist a);
int* odds_remove(int* arr, int arr_size, int n_even);
char* find_char(char* string, char c);
char* copy_char(char* string, int len);
