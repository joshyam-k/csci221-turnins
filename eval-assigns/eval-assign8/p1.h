#include <stdio.h>
#include <vector>
#include <list>
#include <map>
using namespace std;

class car {
private:
    double x;
    double y;
    double mpg;
    double tank_size;
    double current_fuel;
public:
    double getx() const;
    double gety() const;
    double getmpg() const;
    double gettank_size() const;
    double getcurrent_fuel() const;
    void setx(double newx);
    void sety(double newy);
    void setmpg(double newmpg);
    void settank_size(double newtank_size);
    void setcurrent_fuel(double newcurrent_fuel);
    bool move_to(double xnew, double ynew);
    car(double x_, double y_, double mpg_, double tank_size_, double current_fuel_);
    car();
    car(const car &other);
};

class bus : public car {
private:
    int max_passengers;
    vector<int> stop_numbers;
    double gas_penalty;
public:
    bus();
    bus(double x, double y, double mpg, double tank_size, double current_fuel, int max_passengers_, vector<int> stop_numbers_, double gas_penalty_);
    int getmax_passengers() const;
    vector<int> getstop_numbers() const;
    double getgas_penalty()const;
    void setmax_passengers(int max_passengers_);
    void setstop_numbers(vector<int> stop_numbers_);
    void setgas_penalty(double gas_penalty_);
    list<int> generate_route(int starting_stop);
    bool move_to(double xnew, double ynew);
};

class medical_center {
private:
    map<string, string> providers;
    map<string, string> patients;
public:
    medical_center() {}

    void addProvider(string name, string role);

    void addPatient(string name, string condition);

    string getProviderRole(string name);

    string getPatientCondition(string name);
};

class ambulance : public car, public medical_center {
private:
    int max_patients;
    int max_capacity;
    int n_passengers;
    int n_providers;
    double gas_penalty;
public:
    int getmax_patients() const;
    int getmax_capacity() const;
    int getn_passengers() const;
    int getn_providers() const;
    double getgas_penalty() const;
    void setmax_patients(int max_patients_);
    void setmax_capacity(int max_capacity_);
    void setn_passengers(int n_passengers_);
    void setn_providers(int n_providers_);
    void setgas_penalty(double gas_penalty_);
    ambulance();
    ambulance(double x, double y, double mpg, double tank_size, double current_fuel, int max_patients, int max_capacity, int n_passengers, int n_providers, double gas_penalty);
    bool move_to(double xnew, double ynew);
}