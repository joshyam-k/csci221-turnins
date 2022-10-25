#include <stdio.h>

// original version of code as given to us
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

// initial thoughts:
// the dividing by 2 and checking remainders of y makes me think this has something to do with binary


int main(){
    int ret = f(1, 5);
    printf("when we input f(1,5) we get %d\n", ret);
    return 0;
}
