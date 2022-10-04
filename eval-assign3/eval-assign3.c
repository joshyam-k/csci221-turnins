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

node* removal(node* curr, int x){
    if(curr == NULL){
        return NULL;
    }
    if(x > curr->val){
        curr->right = removal(curr->right, x);
    } else if(x < curr->val) {
        curr->left = removal(curr->left, x);
    } else {
        // first case is if it has no children we can just remove the node
        if(curr->right == NULL && curr->left == NULL){
            free(curr);
            return NULL;
        // note we can do || here because we already checked if both are null
        // if there is one child you just replace the node with its child and then free the original node
        } else if(curr->right == NULL || curr->left == NULL){
            //initialize a pointer so that we can free the NULL node and still return the child value
            node* to_keep;
            // need to find which child it is
            if (curr->right == NULL){
                to_keep = curr->left;
            } else {
                to_keep = curr->right;
            }
            free(curr);
            return to_keep;
        } else {
            // finally if there are two children the problem becomes tricky
            // we have to free the node while inserting it's children back into the tree in the correct manner
            // in this case we can just replace the node to be deleted with the smallest valued node to the right of it
            // we then remove that smallest valued node
            node* min_to_right = curr->right;
            while(min_to_right && min_to_right->left != NULL){
                min_to_right = min_to_right->left;
            }
            curr->val = min_to_right->val;
            // we have to clean things up by removing the smallest value to the right of the deleted node since
            // we moved it to the location of the node to be deleted
            curr->right = removal(curr->right, min_to_right->val);
        }
    }
    return curr;
}

// actual code to insert a node
// takes a bst as an argument 
bst insert_node(bst b, int x){
    // remember that b.head is just a pointer to the first node in the bst
    b.head = insert(b.head, x);
    b.length++;
    return b;
}

bst remove_node(bst b, int x){
    b.head = removal(b.head, x);
    return b;
}

bst create_bst(int arr[], int arr_len){
    bst b;
    b.head = NULL;
    b.length = arr_len;
    for(int i = 0; i < arr_len; i++){
        b = insert_node(b, arr[i]);
    }
    return b;
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
    int arr[5] = {1,2,3,4,5};
    bst root = create_bst(arr, 5);
    root = insert_node(root, 10);
    root = remove_node(root, 2);
    view_bst(root.head);
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
