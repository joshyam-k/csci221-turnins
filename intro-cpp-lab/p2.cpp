#include <stdio.h>
#include <iostream>
#include "p2.h"

namespace grading221 {
    double update(double a, double b){
        if (a > b){
            return a;
        } 
        return (a + b)/2.0;
    }
}

void combine(std::string a, std::string b){
    std::cout << "are you a band as in a " << a << " or as in the " << b << "\n"; 
}

int main(){
    double res = grading221::update(1.1, 1.2);
    std::cout << res << "\n";
    combine(musicians::band, rings::band);
    return 0;
}
