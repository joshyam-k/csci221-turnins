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

// helper function to check if a car can move to a location via suffixes of the gas station array
bool move_via_gas_suffix(car c, gasStation* station_array, int gsarray_len, double* cost, double x, double y){
    bool found = false;
    // start at beginning of gas station array and move across it
    // once we can't get to
    int success_index = 0;
    for(int i = 0; i < gsarray_len; i++){
        int possible_success_index = i;
        int moves = 0;
        car copy = c;
        for(int j = i; j < gsarray_len; j++){
            gasStation station = station_array[j];
            bool check = copy.move_to(station.getx(), station.gety());
            if(check == false){
                break; 
            }
            moves++;
            // otherwise continue in loop
        }
        if(moves == (gsarray_len - i)){
            // if made it to the end of the array then final test is to see if it can
            // reach the destination x, y
            bool final_test = copy.move_to(x, y);
            if(final_test == true){
                success_index = possible_success_index;
                found = true;
                break;
            }
            // otherwise continue to next iteration of outer loop
            continue;
        }
    }
    if(found == false){
        return false;
    } else {
        // move car through working suffix and keep track of price
        *cost = 0;
        for (int k = success_index; k < gsarray_len; k++){
            gasStation station = station_array[k];
            bool mv = c.move_to(station.getx(), station.gety());
            *cost += station.getprice();
        }
        bool mv_final = c.move_to(x, y);
        return true;
    }
}

return_mv2 which_can_move2(car* car_array, gasStation* station_array, int carray_len, int gsarray_len, int* return_length,  double x, double y){
    int n_can_move = 0;
    struct return_mv2 struct_return;
    for(int i = 0; i < carray_len; i++){
        car cartest = car_array[i];
        if(cartest.move_to(x, y) == true) {
            n_can_move++;
        } else {
            double cost_dummy = 0;
            if(move_via_gas_suffix(cartest, station_array, gsarray_len, &cost_dummy, x, y) == true) {
                n_can_move++;
            }
        }
    }
    *return_length = n_can_move;
    car* return_array = new car[n_can_move];
    double* cost_array = new double[n_can_move];
    for(int i = 0, j = 0; i < carray_len; i++){
        car carcheck = car_array[i];
        double cost_out = 0;
        if(carcheck.move_to(x,y) == true) {
            return_array[j] = carcheck;
            cost_array[j] = 0;
            j++;
        } else if(move_via_gas_suffix(carcheck, station_array, gsarray_len, &cost_out, x, y ) == true){
            return_array[j] = carcheck;
            cost_array[j] = cost_out;
            j++;
        } else {
            continue;
        }
    }
    struct_return.ret_array = return_array;
    struct_return.c_array = cost_array;
    return struct_return;
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

