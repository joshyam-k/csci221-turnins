#include <memory>
#include <stdio.h>
using namespace std;

template <typename T>
class BSTNode {
public:
  // Constructor
  BSTNode(T data);

  // Accessor methods
  const unique_ptr<T>& getData() const;
  const shared_ptr<BSTNode<T> >& getLeft() const;
  const shared_ptr<BSTNode<T> >& getRight() const;
  const weak_ptr<BSTNode<T> >& getParent() const;

  // Modifier methods
  void setData(const T& data_);
  void setLeft(const shared_ptr<BSTNode<T> >& left_);
  void setRight(const shared_ptr<BSTNode<T> >& right_);
  void setParent(const weak_ptr<BSTNode<T> >& parent_);

private:
  unique_ptr<T> data;
  shared_ptr<BSTNode<T> > left;
  shared_ptr<BSTNode<T> > right;
  weak_ptr<BSTNode<T> > parent;
};


template <typename T>
BSTNode<T>::BSTNode(T data) : data(unique_ptr<T>(new T(data))),
                              left(nullptr),
                              right(nullptr) {}

template <typename T>
const unique_ptr<T>& BSTNode<T>::getData() const {
  return data;
}

template <typename T>
const shared_ptr<BSTNode<T> >& BSTNode<T>::getLeft() const {
  return left;
}

template <typename T>
const shared_ptr<BSTNode<T> >& BSTNode<T>::getRight() const {
  return right;
}

template <typename T>
const weak_ptr<BSTNode<T> >& BSTNode<T>::getParent() const {
  return parent;
}

template <typename T>
void BSTNode<T>::setData(const T& data_) {
  this->data = unique_ptr<T>(new T(data_));
}

template <typename T>
void BSTNode<T>::setLeft(const shared_ptr<BSTNode<T> >& left_) {
  this->left = left_;
}

template <typename T>
void BSTNode<T>::setRight(const shared_ptr<BSTNode<T> >& right_) {
  this->right = right_;
}

template <typename T>
void BSTNode<T>::setParent(const weak_ptr<BSTNode<T> >& parent_) {
  this->parent = parent_;
}


template <typename T>
class BinarySearchTree {
public:
  // Constructor
  BinarySearchTree();
  BinarySearchTree(const T* data, int size);
  ~BinarySearchTree();

  // getters
  const std::shared_ptr<BSTNode<T> >& getRoot() const;
  int getSize() const;

  // setters
  void setRoot(const shared_ptr<BSTNode<T> >& root_);
  void setSize(int size_);

  // Other methods
  void insert(const T& data_);
  int remove(const T& data_);
  pair<shared_ptr<BSTNode<T> >, int>  remove_helper(const shared_ptr<BSTNode<T> >& node, const T& data);
  void destroyTree(const shared_ptr<BSTNode<T> >& node);

private:
  shared_ptr<BSTNode<T> > root;
  int size;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), size(0) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T* data, int size) : root(nullptr), size(0) {
  for (int i = 0; i < size; i++) {
    insert(data[i]);
  }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  destroyTree(root);
}

template <typename T>
void BinarySearchTree<T>::destroyTree(const shared_ptr<BSTNode<T> >& node) {
  if (!node) {
    return;
  }

  destroyTree(node->getLeft());
  destroyTree(node->getRight());
}

template <typename T>
int BinarySearchTree<T>::remove(const T& data_) {
  auto result = remove_helper(root, data_);
  setSize(getSize() - result.second);
  root = result.first;
  return result.second;
}


template <typename T>
pair<shared_ptr<BSTNode<T> >, int> BinarySearchTree<T>::remove_helper(const shared_ptr<BSTNode<T> >& node, const T& data) {
  if (!node) {
    return make_pair(nullptr, 0);
  }

  if (data < *(node->getData())) {
    auto result = remove_helper(node->getLeft(), data);
    node->setLeft(result.first);
    return make_pair(node, result.second);
  } else if (data > *(node->getData())) {
    auto result = remove_helper(node->getRight(), data);
    node->setRight(result.first);
    return make_pair(node, result.second);
  } else {
    if (!node->getLeft() && !node->getRight()) {
      // first case: Node to be removed is a leaf node
      return make_pair(nullptr, 1);
    } else if (!node->getLeft()) {
      // Case 2: Node to be removed has only a right child
      return make_pair(node->getRight(), 1);
    } else if (!node->getRight()) {
      // Case 3: Node to be removed has only a left child
      return make_pair(node->getLeft(), 1);
    } else {
      // Case 4: Node to be removed has two children
      auto largest = node->getLeft();
      while (largest->getRight()) {
        largest = largest->getRight();
      }
      *(node->getData()) = *(largest->getData());
      auto result = remove_helper(node->getLeft(), *(largest->getData()));
      node->setLeft(result.first);
      return make_pair(node, result.second);
    }
  }
}


template <typename T>
const shared_ptr<BSTNode<T> >& BinarySearchTree<T>::getRoot() const {
  return root;
}

template <typename T>
int BinarySearchTree<T>::getSize() const {
  return size;
}

template <typename T>
void BinarySearchTree<T>::setRoot(const shared_ptr<BSTNode<T> >& root_) {
  this->root = root_;
}

template <typename T>
void BinarySearchTree<T>::setSize(int size_) {
  this->size = size_;
}



template <typename T>
void BinarySearchTree<T>::insert(const T& data_) {
  std::shared_ptr<BSTNode<T> > newNode = shared_ptr<BSTNode<T> >(new BSTNode<T>(data_));
  if (root == nullptr) {
    root = newNode;
    size++;
    return;
  }

  shared_ptr<BSTNode<T> > current = root;
  while (true) {
    if (data_ < *(current->getData())) {
      if (current->getLeft() == nullptr) {
        current->setLeft(newNode);
        newNode->setParent(current);
        size++;
        return;
      }
      current = current->getLeft();
    } else {
      if (current->getRight() == nullptr) {
        current->setRight(newNode);
        newNode->setParent(current);
        size++;
        return;
      }
      current = current->getRight();
    }
  }
}