#include <stdint.h>

typedef struct NODE {
    int32_t val;
    struct NODE *left, *right;
} node;

typedef struct BST {
    node* head;
    int length;
} bst;

node* insert(node* curr, int x);
node* removal(node* curr, int x);
bst insert_node(bst b, int x);
int count(node* root);
bst remove_node(bst b, int x, int* n_rm);
bst create_bst(int arr[], int arr_len);
void free_nodes(node* current);
void free_bst(bst* pB);
void view_bst(node* node);
int find_divisors(int* input_arr, int input_len, int n_divs, int** ret_arr1, int** ret_arr2);
int string_eq_check(char* a, char* b);
char* find_string(char* string, char* substring, int str_len);
char* substr_copy(char* string, int start, int end);
