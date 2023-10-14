#include "binary-search-tree-apeer.h"
BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
    avlBalance = 0;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr) {
        return -1;
    }

    int leftDepth = getNodeDepth(n->left);
    int rightDepth = getNodeDepth(n->right);

    if (leftDepth > rightDepth) {
        return leftDepth + 1;
    } else {
        return rightDepth + 1;
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    while (root_ != nullptr) {
        remove(root_->val);
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* loc = root_;

    while (loc->right != nullptr) {
        loc = loc->right;
    }

    return loc->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* loc = root_;

    while (loc->left != nullptr) {
        loc = loc->left;
    }

    return loc->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {

}

bool BinarySearchTree::exists(DataType val) const {
    Node* loc = root_;

    while (loc != nullptr) {
        if (loc->val == val) {
            return true;
        } else if (loc->val > val) {
            loc = loc->left;
        } else {
            loc = loc->right;
        }
    }

    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress(){
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if (exists(val)) {
        return false;
    }

    Node* new_node = new Node(val);
    size_++;

    if (root_ == nullptr) {
        root_ = new_node;
        return true;
    }

    Node* loc = root_;
    bool inserted = false;

    while (!inserted){

        if (val < loc->val) {

            if (loc->left == nullptr) {
                loc->left = new_node;
                inserted = true;
            } else {
                loc = loc->left;
            }

        } else {

            if (loc->right == nullptr) {
                loc->right = new_node;
                inserted = true;
            } else {
                loc = loc->right;
            }

        }

    }

    return true;
}

bool BinarySearchTree::remove(DataType val) {

    Node* parent = nullptr;
    Node* loc = root_;

    while (loc != nullptr && loc->val != val) {

        parent = loc;

        if (val < loc->val) {
            loc = loc->left;
        } else {
            loc = loc->right;
        }

    }

    if (loc == nullptr) {
        return false;
    }

    size_--;

    if (loc->left == nullptr && loc->right == nullptr) {

        if (loc == root_) {
            root_ = nullptr;
        } else if (loc == parent->left) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }

        delete loc;
    }

    else if (loc->left == nullptr || loc->right == nullptr) {

        Node* child = nullptr;

        if (loc->left != nullptr) {
            child = loc->left;
        } else {
            child = loc->right;
        }

        if (loc == root_) {
            root_ = child;
        } else if (loc == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        delete loc;

    }

    else {

        parent = loc;
        Node* leftChild = loc->left;

        while (leftChild->right != nullptr) {
            parent = leftChild;
            leftChild = leftChild->right;
        }

        loc->val = leftChild->val;

        if (leftChild == parent->left) {
            parent->left = leftChild->left;
        } else {
            parent->right = leftChild->left;
        }

        delete leftChild;

    }

    return true;
}