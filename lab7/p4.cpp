#include <stdio.h>
#include <iostream>
#include "p4.h"

void increment(int* p, int x){
    *p = *p + x;
}

void increment2(int &p, int x){
    p = p + x;
}

void increment3(int &p, int x = 1){
    p = p + x;
}

int main(){
    int val = 8;
    int* pval = &val;
    increment(pval, 10);
    increment2(val, 20);
    increment3(val);
    std::cout << "value is now " << *pval;
    return 0;
}
