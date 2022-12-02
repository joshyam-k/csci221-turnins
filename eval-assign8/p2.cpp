#include "p2.h"
#include <iostream>

int main(){
    BST<int> bst;
    bst.addNode(6);
    cout << bst.getCount();
    return 0;
}
