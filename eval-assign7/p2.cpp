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

linkedlist::linkedlist(node* head_, string sortmethod_){
    head = head_;
    sortmethod = sortmethod_;
}

linkedlist::linkedlist(){
    head = nullptr;
    sortmethod = "length";
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

string linkedlist::getsortmethod() const {
    return sortmethod;
}
void linkedlist::setsortmethod(string newsortmethod){
    sortmethod = newsortmethod;
    // this should potentially re-sort the list too
}

bool linkedlist::checksortlength() const {
    if (sortmethod == "length") {
        return true;
    } 
    return false;
}

bool linkedlist::checksortascii() const {
    if (sortmethod == "ascii") {
        return true;
    }
    return false;
}

void linkedlist::sethead(node* head_new){
    head = head_new;
}

string* linkedlist::toarray() const {
    
    node* curr = head;
    int len = this->getlength();
    string* retarr = new string[len];
    for(int i = 0; i < len; i++) {
        retarr[i] = curr->getstr();
        curr = curr->getnext();
    }
    return retarr;
}

void linkedlist::addnode(node newnode){
    // different comparison technique based on sorting method

}

int linkedlist::getlength() const {
    int len = 0;
    node* curr = head;
    while(curr != nullptr){
        len++;
        curr = curr->getnext();
    }
    return len;
}



int main(){
    node node3("hey", nullptr);
    node node2("ya", &node3);
    node node1("man", &node2);
    // node1 -> node2 -> node3 -> null
    linkedlist ll(&node1, "length");
    linkedlist ll2 = ll;
    node1.setstr("test");
    cout << ll2.gethead()->getstr() << ll.gethead()->getstr() << endl;
    cout << ll.getlength() << endl;
    return 0;
}
