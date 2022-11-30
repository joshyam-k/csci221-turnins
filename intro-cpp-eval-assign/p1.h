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

class gasStation {
private:
    double x;
    double y;
    double price;
public:
    double getx() const;
    double gety() const;
    double getprice() const;
    void setx(double newx);
    void sety(double newy);
    void setprice(double newprice);
    gasStation(double x_, double y_, double price_);
    gasStation();
    gasStation(const gasStation &other);
};

struct return_mv2 {
    car* ret_array;
    double* c_array;
};
