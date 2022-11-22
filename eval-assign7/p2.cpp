#include <stdio.h>
#include <cmath>
#include "p2.h"
using namespace std;

node::node(string str_, node* next_ = nullptr){
    str = str_;
    next = next_;
}

node::node(){
    str = "";
    next = nullptr;
}

string node::getstr() const{
   return str; 
}

node* node::getnext() const{
    return next;
}

void node::setstr(string str_new){
    str = str_new;
}

void node::setnext(node* next_new){
    next = next_new;
}

linkedlist::linkedlist(node* head_){
    head = head_;
}

linkedlist::linkedlist(){
    head = nullptr;
}

node* linkedlist::gethead() const {
    return head;
}

string linkedlist::getsortmethod() const{
    return sortmethod;
}

void linkedlist::setsortmethod(string newsortmethod){
    sortmethod = newsortmethod;
}

void linkedlist::sethead(node* head_new){
    head = head_new;
}

void linkedlist::addnode(node newnode){
    // different comparison technique based on sorting method

}



int main(){
    node node1("hey");
    node node2("ya", &node1);
    cout << node2.getnext()->getstr();
    return 0;
}
