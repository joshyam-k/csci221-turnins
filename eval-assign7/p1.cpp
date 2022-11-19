#include <stdio.h>
#include <cmath>
#include <iostream>
#include "p1.h"
using namespace std;

double car::getx() const{
    return x;
}

double car::gety() const{
    return y;
}

double car::getmpg() const{
    return mpg;
}

double car::gettank_size() const{
    return tank_size;
}

double car::getcurrent_fuel() const{
    return current_fuel;
}

void car::setx(double newx){
    x = newx;
}

void car::sety(double newy){
    y = newy;
}

void car::setmpg(double newmpg){
    mpg = newmpg;
}

void car::settank_size(double newtank_size){
    tank_size = newtank_size;
}

void car::setcurrent_fuel(double newcurrent_fuel){
    current_fuel = newcurrent_fuel;
}

car::car(double x_, double y_, double mpg_, double tank_size_, double current_fuel_){
    setx(x_);
    sety(y_);
    setmpg(mpg_);
    settank_size(tank_size_);
    setcurrent_fuel(current_fuel_);
}

car::car(){
    setx(0);
    sety(0);
    setmpg(0);
    settank_size(0);
    setcurrent_fuel(0);
}

car::car(const car &other){
    setx(other.getx());
    sety(other.gety());
    setmpg(other.getmpg());
    settank_size(other.gettank_size());
    setcurrent_fuel(other.getcurrent_fuel());
}

bool car::move_to(double xnew, double ynew){
    double dist = sqrt(pow((xnew - getx()), 2) + pow((ynew - gety()), 2));
    double max_dist = getmpg() * getcurrent_fuel();
    double fuel_used = getmpg() / dist;
    if (dist <= max_dist){
        setx(xnew);
        sety(ynew);
        setcurrent_fuel(getcurrent_fuel() - fuel_used);
        return true;
    }
    return false;
}

double gasStation::getx() const{
    return x;
}

double gasStation::gety() const{
    return y;
}

double gasStation::getprice() const{
    return price;
}

void gasStation::setx(double newx){
    x = newx;
}

void gasStation::sety(double newy){
    y = newy;
}

void gasStation::setprice(double newprice){
    price = newprice;
}

gasStation::gasStation(double x_, double y_, double price_){
    setx(x_);
    sety(y_);
    setprice(price_);
}

gasStation::gasStation(){
    setx(0);
    sety(0);
    setprice(0);
}

gasStation::gasStation(const gasStation &other){
    setx(other.getx());
    sety(other.gety());
    setprice(other.getprice());
}

car* which_can_move(car* array, int array_length, int* return_length,  double x, double y){
    // count how many can move
    int n_can_move = 0;
    for(int i = 0; i < array_length; i++){
        car cartest = array[i];
        if (cartest.move_to(x, y) == true){
            n_can_move++;
        }
    }
    // return length of return array via indirection
    *return_length = n_can_move;
    // allocate space on heap for array of appropriate size and fill it with copies of the cars that can move
    car* return_array = new car[n_can_move];
    for(int i = 0, j = 0; i < array_length; i++){
       car carcheck = array[i];
       bool check = carcheck.move_to(x, y);
       if (check == true){
           return_array[j] = carcheck;
           j++;
       }
    }
    return return_array;
}

int main(){
    car car1(5, 10, 20, 15, 9);
    car car2(1, 2, 20, 15, 9);
    car car3(0, 0, 20, 12, 0.2);
    car car_arr[3] = {car1, car2, car3};
    int newl = 0;
    int* pnewl = &newl;
    car* r_array = which_can_move(car_arr, 3, pnewl, 15, 30);
    return 0;
}

