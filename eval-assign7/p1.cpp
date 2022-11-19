#include <stdio.h>
#include <cmath>
#include <iostream>
#include "p1.h"
using namespace std;

double car::getx(){
    return x;
}

double car::gety(){
    return y;
}

double car::getmpg(){
    return mpg;
}

double car::gettank_size(){
    return tank_size;
}

double car::getcurrent_fuel(){
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




int main(){
    car cartest;
    cartest.setx(5);
    cartest.sety(10);
    cartest.setmpg(20);
    cartest.setcurrent_fuel(10);
    bool out = cartest.move_to(1500, 3000);
    cout << cartest.getx() << "\n";
    cout << cartest.gety() << "\n";
    cout << cartest.getcurrent_fuel() << "\n";
    return 0;
}

