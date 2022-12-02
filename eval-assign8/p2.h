#include <stdio.h>
#include <memory>
using namespace std;

template <typename T>
class BSTNode
{
    public:
        // Constructor
        BSTNode(const T& data) : data_(unique_ptr<T>(new T(data))) {}

        // Getters
        T getData() { return *data_; }
        shared_ptr<BSTNode<T> >& getLeftChild() { return leftChild_; }
        shared_ptr<BSTNode<T> >& getRightChild() { return rightChild_; }
        weak_ptr<BSTNode<T> > getParent() { return parent_; }

        // Setters
        void setData(const T& data) { data_ = unique_ptr<T>( new T(data)); }
        void setLeftChild(const shared_ptr<BSTNode<T> >& node) { leftChild_ = node; }
        void setRightChild(const shared_ptr<BSTNode<T> >& node) { rightChild_ = node; }
        void setParent(const weak_ptr<BSTNode<T> >& node) { parent_ = node; }

    private:
        unique_ptr<T> data_;
        shared_ptr<BSTNode<T> > leftChild_;
        shared_ptr<BSTNode<T> > rightChild_;
        weak_ptr<BSTNode<T> > parent_;
};

template <typename T>
class BST
{
    public:
        // Constructor
        BST() : root_(nullptr), count_(0) {}

        // Getters
        shared_ptr<BSTNode<T> >& getRoot() { return root_; }
        int getCount() { return count_; }

        // Setters
        void setRoot(const shared_ptr<BSTNode<T> >& node) { root_ = node; }
        void setCount(int count) { count_ = count; }

        // Other methods
        void addNode(const T& data);

    private:
        shared_ptr<BSTNode<T> > root_;
        int count_;
};

template <typename T>
void BST<T>::addNode(const T& data)
{
    // Create a new node
    auto newNode = shared_ptr<BSTNode<T> >(new BSTNode<T>(data));
    newNode->setLeftChild(nullptr);
    newNode->setRightChild(nullptr);
    newNode->setParent(nullptr);

    // If tree is empty
    if (root_ == nullptr)
    {
        root_ = newNode;
        count_++;
        return;
    }

    // Otherwise, traverse the tree, find the correct spot, and insert the node
    auto currentNode = root_;
    while (currentNode != nullptr)
    {
        // If data is less than current node
        if (data < *currentNode->getData())
        {
            // Check if left child exists
            if (currentNode->getLeftChild() == nullptr)
            {
                // Create left child
                currentNode->setLeftChild(newNode);
                newNode->setParent(currentNode);
                count_++;
                return;
            }
            // Otherwise, move to left child
            else
            {
                currentNode = currentNode->getLeftChild();
            }
        }
        // If data is greater than current node
        else if (data > *currentNode->getData())
        {
            // Check if right child exists
            if (currentNode->getRightChild() == nullptr)
            {
                // Create right child
                currentNode->setRightChild(newNode);
                newNode->setParent(currentNode);
                count_++;
                return;
            }
            // Otherwise, move to right child
            else
            {
                currentNode = currentNode->getRightChild();
            }
        }
        // If data is equal to current node
        else
        {
            // Do not add duplicate
            return;
        }
    }
}

