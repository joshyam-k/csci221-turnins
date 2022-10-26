#include <stdio.h>

// original version of code as given to us
/*
int f(int x, int y){
    int r = 1;
    while(y > 1){
        if(y % 2 == 1){
            r = x * r;
        }
        x = x * x;
        y = y / 2;
    }
    return r * x;
}
*/

// initial thoughts:
// the dividing by 2 and checking remainders of y makes me think this has something to do with binary
// after running a ton of tests with different inputs on the whiteboards with drop-in tutors we realized that usually this 
// function returns x^y, but when we tested a few edge cases (y = 0 for example) the function did not work as expected
// thus the main work will be to adjust the code so that it works for all viable input values

// one larger change will be to force y to be an unsigned integer since this algorithm simply will not work if it is negative
int f(int x, unsigned int y){
    int r = 1;
    if(y == 0){
        return 1;
    }
    while(y > 1){
        if(y % 2 == 1){
            r = x * r;
        }
        x = x * x;
        y = y / 2;
    }
    return r * x;
}

int main(){
    int ret = f(1, 5);
    printf("when we input f(1,5) we get %d\n", ret);
    return 0;
}
