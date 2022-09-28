#include <stdio.h>
#include <math.h>
#include "eval-assign2.h"

int conditional(int x, int y, int z){
    /*worked on this with omar using logical ! on an integer returns 1 if the integer is zero and 0 if the integer is greater than zero */
    return (!!x * y) + (!x * z);
}


int logical_negation(int a){
    /* in a k-bit int I want to right shift by k-1 positions so I use sizeof(int)*8 which should give me the number of bits used to store an int */
    /* we need to shift both the original integer as well as its additive inverse because we want to eventually get a -1 out of any nonzero value for a*/
    /* if a is zero then op1 and op2 will both be zero, but if a is non-zero then one of them will be zero and the other will be all ones!*/
    int op1 = a >> (sizeof(int)*8 - 1);
    int op2 = (~a + 1) >> (sizeof(int)*8 - 1);
    /*now if we "or" the two of them together we will get zero whenever a was zero and -1 whenever a was nonzero which is exactly what we want */
    int op_final = op1 | op2;
    /*finally we're off by 1 and so we add one to get the desired result */
    /*if a was nonzero then op_final is -1 and so we get 0 */
    /*if a was zero then op_final is 0 so we get 1*/
    return op_final + 1;
}

/* helper function for the next two parts */

int rounder(uint8_t i, int nbitsrm){
    uint8_t rmbits_mask = ~(0xFF << nbitsrm);
    uint8_t rmbits = i & rmbits_mask;
    uint8_t ret_bits;
    uint8_t ret_mask = 0xFF << nbitsrm;
    if(rmbits < pow(2, nbitsrm)) {
        ret_bits = ret_mask & i;
    } else if(rmbits > pow(2, nbitsrm)) {
        ret_bits = (ret_mask & i) + pow(2, nbitsrm + 1);
    } else {
        int rem_bits = i >> nbitsrm;
        if (rem_bits % 2 == 0){
            ret_bits = ret_mask & i;
        } else {
            ret_bits = (ret_mask & i) + pow(2, nbitsrm + 1);
        }
    }
    return ret_bits;
}

int add_tiny(int8_t a, int8_t b){
    /*initializing masks for the different parts of the encoding */
    int8_t sign_mask = 0x80;
    int8_t sigcand_mask = 0x07;
    int8_t exp_mask = 0x78;
    /*I'll use this leading 1 mask to add the implied 1 back into the significand when I need to add them */
    int8_t implied_1_mask = 0x08;
    uint8_t final_ret;
    /*shifting the exponent piece in order to evaluate their size as integers later */
    uint8_t exp_a = (exp_mask & a) >> 3;
    uint8_t exp_b = (exp_mask & b) >> 3;
    int8_t sign_a = (sign_mask & a) >> 7;
    int8_t sign_b = (sign_mask & b) >> 7;
    /*adding the implied 1 back into each significand*/
    int8_t sigcand_a = (sigcand_mask & a) | implied_1_mask;
    int8_t sigcand_b = (sigcand_mask & b) | implied_1_mask;
    /*if the sign bit is one we negate the significand */
    if (sign_a == 1) {
        sigcand_a = ~sigcand_a + 1;
    }
    if (sign_b == 1) {
        sigcand_b = ~sigcand_b + 1;
    }
    /* need to figure out which exponent we need to shift */
    int8_t exp_diff;
    int8_t exp_to_use;
    int8_t sigcand_a_final;
    int8_t sigcand_b_final;
    if (exp_a > exp_b){
        exp_to_use = exp_a;
        /*need to shift sigcand b */
        exp_diff = exp_a - exp_b;
        exp_b = exp_b + exp_diff;
        /* round then shift */
        sigcand_b = rounder(sigcand_b, exp_diff);
        sigcand_b_final = (sigcand_b >> exp_diff);
        sigcand_a_final = sigcand_a;
    } else if(exp_a < exp_b){
        exp_to_use = exp_b;
        /*now need to shift sigcand a */
        exp_diff = exp_b - exp_a;
        exp_a = exp_a + exp_diff;
        /* round then shift */
        sigcand_a = rounder(sigcand_a, exp_diff);
        sigcand_a_final = (sigcand_a >> exp_diff);
        sigcand_b_final = sigcand_b;
    } else {
        exp_to_use = exp_a;
        sigcand_a_final = sigcand_a;
        sigcand_b_final - sigcand_b;
    }
    /*now need to add and potentially round/ increment the exponent*/
    int8_t sigcand_added = sigcand_a_final + sigcand_b_final;
    int8_t add_to_exp;
    int8_t sigcand_f;
    /* a 1 in the 5th bit places */
    if (sigcand_added > pow(2, 3)) {
        printf("need to shift!");
        add_to_exp = 1;
        sigcand_f = (sigcand_added & 0x0F);
        sigcand_f = rounder(sigcand_f, 1);
        sigcand_f = sigcand_f >> 1;
    } else if(sigcand_added < pow(2, 3) && sigcand_added > 2) {
        printf("need to shift!");
        add_to_exp = -1;
        sigcand_f = sigcand_added << 1;
    } else if(sigcand_added < 2) {
        printf("need to shift!");
        add_to_exp = -2;
        sigcand_f = sigcand_added << 2;
    } else {
        add_to_exp = 0;
        sigcand_f = sigcand_added & 0x07;
    } 
    /* adjust and shift the exponent */
    uint8_t exp_f = (exp_to_use + add_to_exp) << 3;
    if ((exp_f - 7) > 7) {
        /* not sure how to return infinity so will just return zero to signify overflow */
        final_ret = 0;
    } else if((exp_f - 7) < -6){
        /* should return zero i think */
        final_ret = 0;
    } else {
        final_ret = sigcand_f | exp_f;
    }
    
    return final_ret;

}

int multiply_tiny(int8_t a, int8_t b){
    /*we will represent the tiny floating points in encoded form since they occupy 8 bits*/
    /*the leading bit is the sign bit, the next 4 bits are the exponent, and the last 3 bits encode the significand*/
    int8_t sign_mask = 0x80;
    int8_t sigcand_mask = 0x07;
    int8_t exp_mask = 0x78;
    int8_t implied_1_mask = 0x08;
    uint8_t final_ret;
    uint8_t exp_a = (exp_mask & a) >> 3;
    uint8_t exp_b = (exp_mask & b) >> 3;
    /* adding the implied leading one before we perform the multiplication of the significands */
    uint8_t sigcand_a = (sigcand_mask & a) | implied_1_mask;
    uint8_t sigcand_b = (sigcand_mask & b) | implied_1_mask;
    /*the simplest step is to find what the sign bit will be */
    int8_t ret_sign = (sign_mask & a) ^ (sign_mask & b);
    
    /*multiplying the significands */
    uint8_t sigcand_mult = sigcand_a * sigcand_b;
    int add_to_exp;
    /* first iteration of the significand */
    uint8_t ret_sigcand;
    /*significand that is correct but just needs to be shifted */
    uint8_t ret_sigcand_unshifted;
    /* final significand */
    uint8_t sigcand_f;
    /*check if we need to shift */
    if (sigcand_mult >= pow(2, 7)) {
        printf("need to shift!\n");
        /*because of the size of these bitstrings the most that we will need to shift the exponent is by 1 */
        add_to_exp = 1;
        ret_sigcand = (sigcand_mult & 0x7F);
        ret_sigcand_unshifted = rounder(ret_sigcand, 4);
        sigcand_f = ret_sigcand_unshifted >> 4;
    } else {
        /*if no need to shift just round and return the product */
        add_to_exp = 0;
        ret_sigcand = sigcand_mult & 0x3F;
        ret_sigcand_unshifted = rounder(ret_sigcand, 3);
        sigcand_f = ret_sigcand_unshifted >> 3;
    } 
    /*this is the first step with the exponent, we will check for overflow later*/
    uint8_t ret_exp = exp_a + exp_b + add_to_exp;
    /*we then shift the exponent and and place it in an 8 bit string */
    uint8_t f_ret_exp = (ret_exp << 3) & 0x78;  
    /* need to check for exponent overflow */
    /* need to find how to assign infinity */
    if ((ret_exp - 7) > 7) {
        /*should return infinity? */
        final_ret = 0;
    } else if((ret_exp - 7) < -6) {
        /* should return 0?*/
        final_ret = 0;
    } else {
        /*if no exponent overflow we just "or" the pieces together to get our final encoding*/
        final_ret = ret_sign | f_ret_exp | sigcand_f; 
    }

    return final_ret;
}

int main(){
    /* lots of random tests */
    int cond = conditional(5, 6, 7);
    int cond2 = conditional(0, 6, 7);
    int res = logical_negation(0);
    int test = multiply_tiny(0x37, 0x37);
    int test2 = multiply_tiny(0x0B, 0x12);
    printf("first returns %d, second returns %d\n", cond, cond2);
    printf("%d\n", res);
    printf("result1 is %d and we expect 110\n", test);
    printf("result2 is %d and we expect 29\n", test2);
    return 0;
}
