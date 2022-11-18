#include <stdio.h>
#include <iostream>

int main(){
    int* px;
    int test = (px == nullptr);
    std::cout << test << "\n";
    int* px_mem = new int;
    delete px_mem;
    int* p_array = new int[17];
    delete [] p_array;
    return 0;
}
