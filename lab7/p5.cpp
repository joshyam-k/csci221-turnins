#include <stdio.h>
#include <iostream>
#include <string>

void increment_user_input(){
    int x;
    std::cout << "Enter an integer\n";
    std::cin >> x;
    x++;
    std::cout << x;
}

void increment_user_input2(){
    std::string x;
    int temp;
    std::cout << "Enter a string of an integer\n";
    std::cin >>  x;
    temp = std::stoi(x);
    temp++;
    std::cout << std::to_string(temp);
}

void increment_user_input3(){

}

int main(int argc, char* argv[]){
    // increment_user_input();
    increment_user_input2();
    return 0;
}
