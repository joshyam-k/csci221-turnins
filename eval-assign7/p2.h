#include <iostream>
using namespace std;

class node {
private:
    string str;
    node* next;
public:
    string getstr() const;
    node* getnext() const;
    void setstr(string str_new);
    void setnext(node* next_new);
    node();
    node(string str_, node* next_);
};

class linkedlist {
private:
    node* head;
    string sortmethod;
public:
    node* gethead() const;
    string getsortmethod() const;
    void sethead(node* head_new);
    void setsortmethod(string newsortmethod);
    linkedlist(node* head_);
    linkedlist();
    // destructor

    void addnode(node newnode);
};
