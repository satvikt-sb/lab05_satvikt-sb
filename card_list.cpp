// card_list.cpp
// Author: Satvik Talchuru
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"

#include <iostream>
using namespace std;

//constructor
card_list::card_list() { 
    root = nullptr;
}
    
// destructor
card_list::~card_list() {
    clear(root);
}

void card_list::clear(Node *n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree
bool card_list::insert(card value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    } else {
        return insert(value, root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool card_list::insert(card value, Node *n) {
    if(n == nullptr){
        n = new Node(value);
        return true;
    }

    if (value == n->info) {
        return false;
    } else if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            return true;
        } else {
            return insert(value, n->left);
        }
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            return true;
        } else {
            return insert(value, n->right);
        }
    }
}

// print tree data in-order, with helper
void card_list::printInOrder() const {
    printInOrder(root);
}

void card_list::printInOrder(Node *n) const {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << (n->info).get_suit() << " " << (n->info).get_value() << endl;
        printInOrder(n->right);
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
card_list::Node* card_list::getNodeFor(card value, Node* n) const{
    if (n == nullptr) {
        return nullptr;  
    }
    else if (n->info == value) {
        return n; 
    } else if (n->info > value) {
        return getNodeFor(value, n->left); 
    } else {
        return getNodeFor(value, n->right); 
    }
}

// returns true if value is in the tree; false if not
bool card_list::contains(card value) const {
    if (getNodeFor(value, root) == nullptr) {
        return false;
    }
    return true;
}

//isEmpty
bool card_list::isEmpty() const {
    if (root == nullptr){
        return true;
    }
    return false;
}

// returns the Node containing the predecessor of the given value
card_list::Node* card_list::getPredecessorNode(card value) const{
    Node* current = getNodeFor(value, root);

    if (current == nullptr) {
        return nullptr;  
    }

    //
    else if (current->left != nullptr) {
        current = current->left;

        while (current->right != nullptr) {
            current = current->right;  
        }
        return current;
    }
    else {
        Node* parent = root;
        Node* predecessor = nullptr;
        while (parent != nullptr) {
            if (value > parent->info) {
                predecessor = parent;
                parent = parent->right;
            } else {
                parent = parent->left;
            }
        }
        return predecessor;
    }
}

// returns the predecessor value of the given value or 0 if there is none
card card_list::getPredecessor(card value) const{
    Node* pred = getPredecessorNode(value);

    if (pred == nullptr) {
        return {'0',"0"};
    } else {
        return pred->info;
    }
}

// returns the Node containing the successor of the given value
card_list::Node* card_list::getSuccessorNode(card value) const{
    Node* current = getNodeFor(value, root);

    if (current == nullptr) {
        return nullptr; 
    }
    else if (current->right != nullptr){
        current = current->right;

        while (current->left != nullptr) {
            current = current->left;  
        }
        return current;
    }
    else {
        Node* parent = root;
        Node* successor = nullptr;
        while (parent != nullptr) {
            if (value < parent->info) {
                successor = parent;  
                parent = parent->left;
            } else {
                parent = parent->right;
            }
        }
    return successor;
    }
}

// returns the successor value of the given value or 0 if there is none
card card_list::getSuccessor(card value) const{
    Node* succ = getSuccessorNode(value);

    if (succ == nullptr) {
        return {'0',"0"};
    } else {
        return succ->info;
    }
}

//finding rightmost node
card card_list::findMax() const {
    Node* node = root;
    while (node && node->right) {
        node = node->right;
    }
    return node->info;
}

//find the leftmost node
card card_list::findMin() const {
    Node* node = root;
    while (node && node->left) {
        node = node->left;
    }
    return node->info;
}

bool card_list::remove(card value){
    if (!contains(value)){
        return false;
    }

    Node* delNode = getNodeFor(value, root);
    //0 children
    if (delNode-> left == nullptr && delNode->right == nullptr){
        if(delNode->parent == nullptr){
            root = nullptr;
        } else if (delNode->parent->right == delNode){
            delNode->parent->right = nullptr;
        } else {
            delNode->parent->left = nullptr;
        }
        delete delNode;
    }
    //1 child
    else if (delNode->left == nullptr || delNode->right == nullptr) {
        Node* child = (delNode->left) ? delNode->left : delNode->right;

        if (delNode->parent == nullptr) {
            root = child;  // The node to remove is the root
            root->parent = nullptr;
        } else if (delNode->parent->right == delNode) {
            delNode->parent->right = child;
        } else {
            delNode->parent->left = child;
        }

        child->parent = delNode->parent;
        delete delNode;
    }
    else {
        Node* successor = getSuccessorNode(delNode->info);
        card succ_val = successor->info;

        remove(succ_val);
        delNode->info = succ_val;
    }

    return true;
}


