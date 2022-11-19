#include <stdio.h>
#include <iostream>
#include "p6.h"
#include <algorithm>
using namespace std;

void cc_count(string input_s, CharacterCount* x){
    string cc_string = x->s;
    int* arr = x->array;
    int length = cc_string.length();
    for(int i = 0; i < length; i++){
        char curr = cc_string.at(i);
        string::difference_type n = count(input_s.begin(), input_s.end(), curr);
        arr[i] = arr[i] + n;
    }
}

string CharacterCount::getS(){
    return s;
}

int* CharacterCount::getArr(){
    return array;
}

void CharacterCount::setS(string new_s){
    if (new_s.length() != s.length()){
    // do nothing
    } else {
        s = new_s;
    }
}

void CharacterCount::setArr(int* new_arr){
    for(int i = 0; i < s.length(); i++){
        array[i] = new_arr[i];
    }    
}

int CharacterCount::operator[](int index){
    int* arr = getArr();
    return arr[index];
}


int main(){
    CharacterCount cc;
    CharacterCount* pcc = &cc;
    cc.s = "yay";
    cc.array[0] = 1;
    cc.array[1] = 2;
    cc.array[2] = 3;
    cc_count("jaa", pcc);
    cout << cc.array[0] << " " << cc.array[1] << " " << cc.array[2];
    return 0;
}
