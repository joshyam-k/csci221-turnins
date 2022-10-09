#include <stdio.h>
#include <math.h>

int int_max(int n){
    int total = 0;
    // use n-1 since these are signed ints so int max is all ones except for the leading bit
    for(int i = 0; i < (n - 1); i++){
        total = total + pow(2, i); 
    }
    return total;
}

int64_t overflow(int32_t a, int32_t b){
    // define int max
    int INTMAX = int_max(32);
    int64_t res;
    // first overflow check
    if (b >= 0 && a > (INTMAX - b)) {
        res = ((int64_t) (a + b)) + pow(2, 32);
    } else if(b < 0 && a < (INTMAX - b)) {
        res = ((int64_t) (a + b)) - pow(2, 32);
    } else {
        res = (int64_t) (a + b);
    }
    return res;
}

int main(){
    int64_t test = overflow(0x80000000, 0x80000000);
    printf("the result is %lld\n", test);
    return 0;
}
