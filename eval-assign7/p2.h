#include <iostream>
using namespace std;

class node {
private:
    string str;
    node* next;
public:
    string getstr() const;
    node* getnext() const;
    void setstr(int str_new);
    void setnext(node* next_new);
    node();
    node(string str_);
};
