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
// thus we mostly just have to fix the algorithm for the case when y is zero


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

// we will run several tests
// first we will test for a valid case and an edge case
// then we will try a case where y is negative
// then we will try a case when x and y are of the wrong type
// then we will try a case where x is of a different incorrect type

// as desired the function works as we want it to work for the first 2 cases
// normally it would probably just throw an warning for the last 3 cases but because of the flags we include 
// in our makefile, these warnings are treated as errors and the program will not complete for these cases.
// in particular the last case is especially dangerous because it will invoke undefined behavior

int main(){
    int t1 = f(2, 8);
    int t2 = f(2, 0);
    int t3 = f(2, -8);
    int t4 = f(1.1, 1.9);
    int t5 = f("c", 3);
    printf("f(2, 8) = %d, f(2,0) = %d, f(2, -8) = %d, f(1.1,1.9) = %d, f(c, 3) = %d", t1, t2, t3, t4, t5);
    return 0;
}









