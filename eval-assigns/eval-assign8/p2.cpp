#include "BSTNode.h"
#include <iostream>

int main() {
  // Create a new binary search tree.
  int data[] = {10, 5, 15, 3, 7, 12, 17};
  int size = sizeof(data) / sizeof(data[0]);

  BinarySearchTree<int> bst(data, size);

  // Print the size of the tree
  cout << "Tree size: " << bst.getSize() << endl;

  int removed = bst.remove(15);

  cout << removed << endl;

  cout << "Tree size is now: " << bst.getSize() << endl;
  return 0;
}

