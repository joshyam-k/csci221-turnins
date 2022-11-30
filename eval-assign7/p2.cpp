#include <stdio.h>
#include <string>
#include <cmath>
#include "p2.h"


node::node(string str_, node* next_ = nullptr){
    setstr(str_);
    setnext(next_);
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
    sethead(head_);
    setsortmethod(sortmethod_);
}

linkedlist::linkedlist(){
    sethead(nullptr);
    setsortmethod("length");
}

linkedlist::~linkedlist(){
    node* curr = head;
    while(curr != nullptr){
        node* next = head->getnext();
        node* temp = new node;
        temp = curr;
        delete temp;
        curr = next;
    }
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
    this->sort();
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

void linkedlist::rmvalue(string value){
    node* headcp = head;
    // case for when the head node contains the value
    if(headcp != nullptr && headcp->getstr() == value){
        node* todelete = new node();
        todelete = head;
        delete todelete;
        head = headcp->getnext();
    }
    node* curr = head;
    node* prev = nullptr;
    while(curr != nullptr){
        if(curr->getstr() != value){
            prev = curr;
            curr = curr->getnext();
        } else {
            // create a temp pointer the node to be deleted
            node* temp = new node();
            temp = curr;
            prev->setnext(curr->getnext());
            // prev unchanged
            // delete the node
            delete temp;
            // move curr
            curr = curr->getnext();
        } 
    }
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

string linkedlist::getstr_byindex(int index) const {
    int len = this->getlength();
    if(index >= len) {
        cout << "index out of range \n";
        return 0;
    } else {
        string* arr;
        arr = this->toarray();
        return arr[index];
    }
}

// returns true if ascii encoding of a < ascii encoding b
bool linkedlist::compare_ascii(string a, string b){
    bool done = false;
    bool ret;
    int i = 0;
    while(!done){    
        if(a[i] == b[i]){
            i++;
            continue;
        }
        if(int(a[i]) < int(b[i])){
            done = true;
            ret = true;
        } else {
            done = true;
            ret = false;
        }
    }
    return ret;
}

void linkedlist::insert_by_length(node* newnode){
    int len = newnode->getstr().length();
    node* curr = head;
    node* prev = nullptr;
    if(curr != nullptr && len < curr->getstr().length()){
        // then the new node should be the head
        newnode->setnext(curr);
        this->sethead(newnode);
        return;
    }
    while(curr->getnext() != nullptr && curr->getstr().length() < len){
        prev = curr;
        curr = curr->getnext();
    }
    if(curr->getnext() == nullptr){
        if(curr->getstr().length() >= len){
            newnode->setnext(curr);
            prev->setnext(newnode);
            return;
        }
        newnode->setnext(curr->getnext());
        curr->setnext(newnode);
        return;
    } else {
        newnode->setnext(curr);
        prev->setnext(newnode);
        return;
    }
}

void linkedlist::insert_by_ascii(node* newnode){
    node* curr = head;
    node* prev = nullptr;
    if(curr != nullptr && compare_ascii(newnode->getstr(), curr->getstr())){
        // if newnode < head then new node should be the head
        newnode->setnext(curr);
        this->sethead(newnode);
        return;
    }
    // while the next node is not null AND curr_ascii < newnode_ascii then move forward
    while(curr->getnext() != nullptr && compare_ascii(curr->getstr(), newnode->getstr())){
        prev = curr;
        curr = curr->getnext();
    }
    if(curr->getnext() == nullptr){
        if(!compare_ascii(curr->getstr(), newnode->getstr())){
            // if newnode_ascii <= curr_ascii
            newnode->setnext(curr);
            prev->setnext(newnode);
            return;
        }
        newnode->setnext(curr->getnext());
        curr->setnext(newnode);
    } else {
        newnode->setnext(curr);
        prev->setnext(newnode);
        return;
    }
}

void linkedlist::insert_node(string str_in){
    //node nn(str_in, nullptr);
    node* nn_ptr = new node(str_in, nullptr);
    //nn_ptr = &nn;
    if(head == nullptr){
        sethead(nn_ptr);
        return;
    }
    // different comparison technique based on sorting method
    if(sortmethod == "length"){
        this->insert_by_length(nn_ptr);
    } else if(sortmethod == "ascii"){
        this->insert_by_ascii(nn_ptr);
    }
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

void linkedlist::sort() {
    int count = this->getlength();
    string* arr = this->toarray();
    this->~linkedlist();
    for(int i = 0; i < count; i++){
        this->insert_node(arr[i]);
    }
}

void linkedlist::view() const {
    node* curr = head;
    while(curr != nullptr){
        cout << curr->getstr() << endl;
        curr = curr->getnext();
    }
}




int main(){
    // init
    linkedlist ll(nullptr, "ascii");
    // insert node recognizes the sort method and adds them accordingly
    ll.insert_node("Zap");
    ll.insert_node("Botanical");
    ll.insert_node("Saint");
    ll.insert_node("Gander");
    ll.view();
    // if we change the sort method it re-sorts the list
    ll.setsortmethod("length");
    ll.view();
    // we can remove values
    ll.rmvalue("Zap");
    ll.view();
    // we can insert values 
    ll.insert_node("joshyamamoto");
    ll.view();
    // we can get a string by its index (1 base index is used here)
    cout << ll.getstr_byindex(1) << endl;
    // we can free our linked list using our destructor
    ll.~linkedlist();
    return 0;
}
