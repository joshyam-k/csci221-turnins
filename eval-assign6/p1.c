#include <stdio.h>
#include <stdint.h>

uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay){
    if(length <= 0){
        return 0;
    }
    uint32_t rest = decaying_sum(&values[1], length - 1, decay);
    printf("currently rest is %d\n", rest);
    uint32_t decayed = rest/decay;
    printf("returning is %d\n", values[0] + decayed);
    return values[0] + decayed;
}

int main(){
    uint16_t values[6] = {20,2,4,8,16,32};
    uint32_t test = decaying_sum(values, 8, 10);
    printf("res is %d", test);
    return 0;
}

// length greater than 0 so continue
// rest = decaying_sum(values + 1, 1, 10)
// length greater than 0 so continue
// rest = decaying_sum(values + 2, 0, 10)
// length is 0 so return 0
