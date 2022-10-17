#include <stdio.h>

// given version
// with added comments

int f(int x, int y){
    int r = 1;
    while(y > 1){
        // if y is odd then multiply r by x
        // alternatively if y has a 1 in its binary representation in that spot
        // then multiply r by x
        // so you can think of this while loop working bit by bit through the binary 
        // representation of y
        if (y % 2 == 1){
            r = x * r;
        }
        // square x
        x = x * x;
        // divide y by 2
        y = y / 2;
    }
    // finally return r*x
    return r*x;
}

int main(){
    printf("testing %d\n", f(5, 10));
    return 0;
}
