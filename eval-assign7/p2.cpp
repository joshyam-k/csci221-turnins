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

// deep copies copy constructor
linkedlist::linkedlist(const linkedlist &other){
    if (other.gethead() == nullptr){
        head = nullptr;
    } else {
        head = new node(other.gethead()->getstr());
        node* curr = head;
        node* otherhead = other.gethead();
        node* currobj = otherhead;
        while(currobj->getnext() != nullptr){
            curr->setnext(new node(currobj->getnext()->getstr()));
            currobj = currobj->getnext();
            curr = curr->getnext();
        }
    }
}

node* linkedlist::gethead() const {
    return head;
}
/*
string linkedlist::getsortmethod() const{
    return sortmethod;
}
void linkedlist::setsortmethod(string newsortmethod){
    sortmethod = newsortmethod;
    // this should potentially re-sort the list too
}
*/

void linkedlist::sethead(node* head_new){
    head = head_new;
}

void linkedlist::addnode(node newnode){
    // different comparison technique based on sorting method

}



int main(){
    node node3("hey");
    node node2("ya", &node3);
    node node1("man", &node2);
    // node1 -> node2 -> node3 -> null
    linkedlist ll(&node1);
    linkedlist ll2 = ll;
    cout << ll2.gethead()->getstr() << ll.gethead()->getstr() << endl;
    return 0;
}
