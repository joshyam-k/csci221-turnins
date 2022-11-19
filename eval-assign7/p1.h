class car {
private:
    double x;
    double y;
    double mpg;
    double tank_size;
    double current_fuel;
public:
    double getx();
    double gety();
    double getmpg();
    double gettank_size();
    double getcurrent_fuel();
    void setx(double newx);
    void sety(double newy);
    void setmpg(double newmpg);
    void settank_size(double newtank_size);
    void setcurrent_fuel(double newcurrent_fuel);
    bool move_to(double xnew, double ynew);
};
