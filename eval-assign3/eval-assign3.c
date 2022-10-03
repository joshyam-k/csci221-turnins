#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eval-assign3.h"

// helper function to insert a node
// returns a pointer to the head node of the bst
node* insert(node* curr, int x){
    // once we find where the value should be added we create a new node for it
    // we have to allocate memory for it so that it survives beyond the function call
    if(curr == NULL){
        node* temporary = (node*)malloc(sizeof(node));
        temporary->val = x;
        temporary->left = temporary->right = NULL;
        return temporary;
    }
    // if x is less than *(curr).val then move to the left in the BST and work recursively
    if(x < curr->val){
        curr->left = insert(curr->left, x);
        return curr;
    // if x is greater than *(curr).val then move to the right in the BST and work recursively
    } else {
        curr->right = insert(curr->right, x);
        return curr;
    }
}

void insert_node(bst b, int x){    
    // we're being fed an initialized bst 
    // and we need to insert a node in it
    // intitialize a pointer to the head of the bst
    node* current = b.head;
    current = insert(current, x);
}

void view_bst(node* node){
    if(node != NULL){
        view_bst(node->left);
        printf("%d\n", node->val);
        view_bst(node->right);
    }
}

int find_divisors(int* input_arr, int input_len, int n_divs, int** ret_arr1, int** ret_arr2){
    if(n_divs == 0){
        *ret_arr1 = malloc(sizeof(int));
        *ret_arr2 = malloc(sizeof(int));
        *ret_arr1[0] = 0;
        *ret_arr2[0] = 0;
        return 0;
    }
    *ret_arr1 = malloc(n_divs * sizeof(int));
    *ret_arr2 = malloc(n_divs * sizeof(int));
    for(int i = 0; i < n_divs; i++){
        *(*ret_arr1 + i) = input_arr[i];
        *(*ret_arr2 + i)= input_arr[i];
    }
    for(int i = 0; i < input_len; i++){
        for(int j = (i + 1), n_divs_count = 0; j < input_len; j++){
            if(input_arr[i] % input_arr[j] == 0){
                *(*ret_arr1 + n_divs_count) = input_arr[j];
                *(*ret_arr2 + n_divs_count) = input_arr[i];
                n_divs_count++;
            } else if(input_arr[j] % input_arr[i] == 0){
                *(*ret_arr1 + n_divs_count) = input_arr[i];
                *(*ret_arr2 + n_divs_count) = input_arr[j];
                n_divs_count++;
            }
        }
    }
    return 0;

}

// helper function for p3
int string_eq_check(char* a, char* b){
    // same thing as while(*a != '\0' && *b != '\0')
    while(*a && *b){
        // if the first elements of a and b are not the same then return 0
        // the strings in this case are not the same
        if(*a != *b){
            return 0;
        }
        // otherwise iterate and keep checking
        a++;
        b++;
    }
    // if the loop breaks and *b == '\0' then the strings are the same
    // because we made it through the whole string without returning 0
    return (*b == '\0');
}

char* find_string(char* string, char* substring, int str_len){
    while(*string != '\0'){
        // we start by finding the first instance of the first character in substring in string
        // we then check if the letters following that instance give us the substring
        // if they do we return the pointer to that string
        // otherwise we iterate the string and keep checking
        if(*string == *substring && string_eq_check(string, substring)){
            return string;
        }
        string++;
    }
    // if no instance exists return a pointer to the termination character in the original string
    char* ret_p = &string[str_len + 1];
    return ret_p;
    
}

char* substr_copy(char* string, int start, int end){
    /* add 1 since we will have to add the NUL character at the end */
    int len = end - start + 1;
    char* substr = malloc(len*sizeof(char));
    for(int i = start, len_count = 0; i <= end; i++){
        if(i == end){
            substr[len_count] = '\0';
        } else {
            substr[len_count] = string[i];
        }
        len_count++;
    }
    return substr;
}

int main(){
    bst b;
    b.head = NULL;
    b.length = 2;
    /*
    b.length = 2;
    b.head = (node*)malloc(sizeof(node));
    b.head->val = 50;
    b.head->right = b.head->left = NULL;
    */
    insert_node(b, 10);
    printf("test %d\n", b.head->val);
    //view_bst(b.head);
    //printf("test %d\n", b.head->left->val);
    /*
    b.head->val = 50;
    b.head->right = NULL;
    b.head->left = NULL;
    printf("testing %d\n", b.head->val);
    free(b.head);
    */
    /*
    int a[4] = {2, 3, 4, 10};
    int* ret_a1;
    int* ret_a2;
    int res = find_divisors(a, 4, 2, &ret_a1, &ret_a2);
    for(int i = 0; i< 2; i++){
        printf("testing %d\n", ret_a1[i]);
        printf("testing %d\n", ret_a2[i]);
    }
    char* inp_str = "hello";
    char* ret_str = substr_copy(inp_str, 1, 3);
    char* test_str = "hello mr grader";
    char* test_substr = "mr grader";
    char* ret_test = find_string(test_str, test_substr, 15);
    printf("found and it is %s\n", ret_test);
    printf("we subset hello and get %s\n", ret_str);
    */
    return 0;
}
