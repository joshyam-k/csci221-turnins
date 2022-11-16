#include <stdio.h>
#include <stdint.h>
#include <math.h>

uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay){
    if(length <= 0){
        return 0;
    }
    uint32_t rest = decaying_sum(&values[1], length - 1, decay);
    uint32_t decayed = rest/decay;
    return values[0] + decayed;
}

// my tail recursive version
uint32_t decay_t(uint16_t* values, uint16_t length, uint16_t decay, uint32_t total, int i){
    if(i > length){
        return total;
    }
    uint32_t decayed = (uint32_t) pow(decay, length - i);
    uint32_t res = (uint32_t) (values[length - i]/decayed);
    total = total + res;
    i++;
    return decay_t(values, length, decay, total, i);
}

// full use here
uint32_t decay(uint16_t* values, uint16_t length, uint16_t decay){
    uint32_t total = 0;
    int i = 1;
    return decay_t(values, length, decay, total, i);
}


int main(){
    uint16_t values[8] = {1,2,3,20, 4,5, 10, 12};
    uint32_t test2 = decay(values, 7, 1);
    uint32_t test = decaying_sum(values, 7, 1);
    printf("we got %d and we expected %d", test2, test);
    return 0;
}

