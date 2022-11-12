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
    uint32_t res = values[length - i]/pow(decay, length);
    total = total + res;
    i++;
    return decay_t(values, length, decay, total, i);
}

uint32_t decay(uint16_t* values, uint16_t length, uint16_t decay){
    uint32_t total = 0;
    int i = 1;
    return decay_t(values, length, decay, total, i);
}




uint32_t decay_loop(uint16_t* values, uint16_t length, uint16_t decay) {
    uint32_t total = 0; //values[0];    // this term always included in the sum
    for (int i = 1; i <= length; i++) {
        uint32_t res = values[length - i]/pow(decay, length);
        total = total + res;
    }
    return total;
}

int main(){
    uint16_t values[6] = {1,2,3,4,5};
    uint32_t test2 = decay(values, 3, 1);
    uint32_t test = decaying_sum(values, 3, 1);
    printf("we got %d and we expected %d", test2, test);
    return 0;
}

// length greater than 0 so continue
// rest = decaying_sum(values + 1, 1, 10)
// length greater than 0 so continue
// rest = decaying_sum(values + 2, 0, 10)
// length is 0 so return 0
