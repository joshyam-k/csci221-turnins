#include <stdio.h>
#include <memory>
using namespace std;

template <typename T>
class BSTNode {
private:
    unique_ptr<T> data;
    shared_ptr<BSTNode<T> > left;
    shared_ptr<BSTNode<T> > right;
    weak_ptr<BSTNode<T> > parent;
public:
    BSTNode(T data) { this->data = unique_ptr<T>(new T(data)); }
    void setLeft(shared_ptr<BSTNode<T> >& left) { this->left = left; }
    void setRight(shared_ptr<BSTNode<T> >& right) { this->right = right; }
    void setParent(weak_ptr<BSTNode<T> >& parent) { this->parent = parent; }
    T getData() const { return *data; }
    shared_ptr<BSTNode<T> >& getLeft() { return left; }
    shared_ptr<BSTNode<T> >& getRight() { return right; }
    weak_ptr<BSTNode<T> >& getParent() { return parent; }
};


template <class T>
class BST {
private:
    shared_ptr<BSTNode<T> > root; // pointer to the root node of the tree
    int count; // number of elements in the tree
public:
    // Constructor
    BST() : root(nullptr), count(0) {}
    std::shared_ptr<BSTNode<T> > getRoot() const { return root; };
    int getCount() const { return count; };
    void setRoot(std::shared_ptr<BSTNode<T> > root) { this->root = root; };
    void setCount(int count) { this->count = count; };
    // Other methods
    void insert(T data);
    void remove(T data);
    void search(T data);
    void inOrderTraversal() const;
};


template <class T>
void BST<T>::insert(T data) {
    // Allocate a new node
    shared_ptr<BSTNode<T> > newNode = make_shared<BSTNode<T> >(data);

    // If the tree is empty, make the root node the new node
    if (root == nullptr) {
        this->root = newNode;
    } else {
        // Start at the root node
        shared_ptr<BSTNode<T> > currentNode = root;
        // Iterate through the tree
        while (true) {
            // If the data is less than the current node's data, go left
            if (data < currentNode->getData()) {
                if (currentNode->getLeft() == nullptr) {
                    // Insert the new node as the left child
                    currentNode->setLeft(newNode);
                    // Set the parent of the new node
                    newNode->setParent(currentNode);
                    break;
                } else {
                    currentNode = currentNode->getLeft();
                }
            } else {
                // If the data is greater than or equal to the current node's data, go right
                if (currentNode->getRight() == nullptr) {
                    // Insert the new node as the right child
                    currentNode->setRight(newNode);
                    // Set the parent of the new node
                    newNode->setParent(currentNode);
                    break;
                } else {
                    currentNode = currentNode->getRight();
                }
            }
        }
    }

    // Increase the count
    count++;
}

template <class T>
void BST<T>::remove(T data) {
    // If the tree is empty, do nothing
    if (root == nullptr) {
        return;
    }

    // Start at the root node
    std::shared_ptr<BSTNode<T> > currentNode = root;
    std::shared_ptr<BSTNode<T> > parentNode = nullptr;

    // Iterate through the tree
    while (currentNode != nullptr) {
        // If the data is equal to the current node's data
        if (data == currentNode->getData()) {
            // If the current node has no left child
            if (currentNode->getLeft() == nullptr) {
                // If the parent node is null, the current node is the root node
                if (parentNode == nullptr) {
                    // Set the root to the current node's right child
                    this->root = currentNode->getRight();
                } else {
                    // Set the parent's left/right child to the current node's right/left child
                    if (parentNode->getLeft() == currentNode) {
                        parentNode->setLeft(currentNode->getRight());
                    } else {
                        parentNode->setRight(currentNode->getLeft());
                    }
                }
            } else {
                // Find the rightmost node in the left subtree
                std::shared_ptr<BSTNode<T> > rightmostNode = currentNode->getLeft();
                std::shared_ptr<BSTNode<T> > rightmostParentNode = currentNode;

                while (rightmostNode->getRight() != nullptr) {
                    rightmostParentNode = rightmostNode;
                    rightmostNode = rightmostNode->getRight();
                }

                // Replace the current node's data with the rightmost node's data
                currentNode->setData(rightmostNode->getData());

                // Remove the rightmost node from the tree
                if (rightmostParentNode->getLeft() == rightmostNode) {
                    rightmostParentNode->setLeft(rightmostNode->getLeft());
                } else {
                    rightmostParentNode->setRight(rightmostNode->getLeft());
                }
            }

            // Decrease the count
            count--;
            return;
        } else {
            // If the data is less than the current node's data, go left
            if (data < currentNode->getData()) {
                parentNode = currentNode;
                currentNode = currentNode->getLeft();
            } else {
                // If the data is greater than or equal to the current node's data, go right
                parentNode = currentNode;
                currentNode = currentNode->getRight();
            }
        }
    }
}









