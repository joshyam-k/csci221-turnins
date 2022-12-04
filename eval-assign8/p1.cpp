#include <cmath>
#include <iostream>
#include <algorithm>
#include "p1.h"
using namespace std;

// car implementation

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


//  bus implementations

int bus::getmax_passengers() const {
    return max_passengers;
}

vector<int> bus::getstop_numbers() const {
    return stop_numbers;
}

double bus::getgas_penalty() const {
    return gas_penalty;
}

void bus::setmax_passengers(int max_passengers_) {
    this->max_passengers = max_passengers_;
}

void bus::setstop_numbers(vector<int> stop_numbers_) {
    this->stop_numbers = stop_numbers_;
}

void bus::setgas_penalty(double gas_penalty_) {
    this->gas_penalty = gas_penalty_;
}

bus::bus() : car(){
    setmax_passengers(0);
    vector<int> v;
    setstop_numbers(v);
    setgas_penalty(0);
}

// calls car constructor too
bus::bus(double x, double y, double mpg, double tank_size, double current_fuel, int max_passengers_, vector<int> stop_numbers_, double gas_penalty_) : car(x, y, mpg, tank_size, current_fuel) {
    setmax_passengers(max_passengers_);
    setstop_numbers(stop_numbers_);
    setgas_penalty(gas_penalty_);
}

list<int> bus::generate_route(int starting_stop) {
    // sort and get unique version of vector
    sort(stop_numbers.begin(), stop_numbers.end());
    stop_numbers.erase(unique(stop_numbers.begin(), stop_numbers.end()), stop_numbers.end());
    // remove starting stop, so we can add it to the beginning
    stop_numbers.erase(remove(stop_numbers.begin(), stop_numbers.end(), starting_stop), stop_numbers.end());
    // place it at the beginning of the vector
    stop_numbers.insert(stop_numbers.begin(), starting_stop);
    // initialize return list
    list<int> ret;
    for(int i = 0; i < stop_numbers.size(); i++){
        ret.push_back(stop_numbers[i]);
    }
    return ret;
}

bool bus::move_to(double xnew, double ynew) {
    double dist = sqrt(pow((xnew - getx()), 2) + pow((ynew - gety()), 2));
    double weighted_mpg = getmpg()*getgas_penalty()*getstop_numbers().size();
    double max_dist = weighted_mpg * getcurrent_fuel();
    double fuel_used = weighted_mpg / dist;
    if (dist <= max_dist){
        setx(xnew);
        sety(ynew);
        setcurrent_fuel(getcurrent_fuel() - fuel_used);
        return true;
    }
    return false;
}

void medical_center::addProvider(string name, string role) {
    providers[name] = role;
}

void medical_center::addPatient(string name, string condition) {
    patients[name] = condition;
}

string medical_center::getProviderRole(string name) {
    return providers[name];
}

string medical_center::getPatientCondition(string name) {
    return patients[name];
}

int ambulance::getmax_patients() const {
    return max_patients;
}

int ambulance::getmax_capacity() const {
    return max_capacity;
}

double ambulance::getgas_penalty() const {
    return gas_penalty;
}

void ambulance::setmax_patients(int max_patients_) {
    max_patients = max_patients_;
}

void ambulance::setmax_capacity(int max_capacity_) {
    max_capacity = max_capacity_;
}

void ambulance::setgas_penalty(double gas_penalty_) {
    gas_penalty = gas_penalty_;
}

ambulance::ambulance() : car() {
    setmax_patients(0);
    setmax_capacity(0);
    setgas_penalty(0);
}

ambulance::ambulance(double x, double y, double mpg, double tank_size, double current_fuel, int max_patients, int max_capacity, int gas_penalty) : car(x, y, mpg, tank_size, current_fuel) {
    setmax_patients(maxpatients);
    setmax_capacity(max_capacity);
    setgas_penalty(gas_penalty);
}


int main(){
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(3);
    v.push_back(2);
    v.push_back(5);
    v.push_back(1);
    v.push_back(10);
    bus bus1(0, 0, 20, 40, 15, 5, v, 0.02);
    list<int> out = bus1.generate_route(10);
    for (auto it = out.begin(); it != out.end(); ++it) {
    // Print the current element
    cout << *it << " ";
    }

    bool test = bus1.move_to(1,1);
    cout << endl << test << endl;

    return 0;
}