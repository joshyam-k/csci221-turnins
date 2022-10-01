#include <stdio.h>
#include <stdlib.h>
#include "eval-assign3.h"




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


int main(){
    int a[4] = {2, 3, 4, 10};
    int* ret_a1;
    int* ret_a2;
    int res = find_divisors(a, 4, 2, &ret_a1, &ret_a2);
    for(int i = 0; i< 2; i++){
        printf("testing %d\n", ret_a1[i]);
        printf("testing %d\n", ret_a2[i]);
    }
    return 0;
}
