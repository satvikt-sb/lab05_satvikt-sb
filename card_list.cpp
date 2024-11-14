// card_list.cpp
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"

#include <iostream>
using namespace std;

//constructor
card_list::card_list() { 
    root = nullptr;
}
    
// destructor deletes all nodes
card_list::~card_list() {
    clear(root);
}

//destructor
void card_list::clear(Node *n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value
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
    if(!n){
        n = new Node(value);
        return true;
    }
    if (value < n->info) {
        if (!n->left) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left);
        }
    } else if (value > n->info) {
        if (!n->right) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    } else {
        return false;
    }
}

//in-order traversal
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

bool card_list::contains(card value) const {
    if (getNodeFor(value, root) == nullptr){
        return false;
    }
    return true;
}

bool card_list::isEmpty() const {
    if (root == nullptr){
        return true;
    }
    return false;
}

// rightmost node
card card_list::findMax() const {
    Node* node = root;
    while (node && node->right) {
        node = node->right;
    }
    return node->info;
}

// leftmost node
card card_list::findMin() const {
    Node* node = root;
    while (node && node->left) {
        node = node->left;
    }
    return node->info;
}


// returns the Node containing the predecessor of the given value
card_list::Node* card_list::getPredecessorNode(card value) const{
    Node* curr = getNodeFor(value, root);

    if (curr == nullptr){
        return nullptr;
    }

    else if (curr->left != nullptr){
        curr = curr->left;

        while (curr->right != nullptr){
            curr = curr->right;
        }
        return curr;
    }

    else {
        Node* parent = curr->parent;
        while (parent != nullptr && curr == parent->left) {
            curr = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

card card_list::getPredecessor(card value) const{
    Node* pred = getPredecessorNode(value);

    if(pred == nullptr){
        return {'0',"0"};
    } else {
        return pred->info;
    }
}

// returns the Node containing the successor of the given value
card_list::Node* card_list::getSuccessorNode(card value) const{
    Node* curr = getNodeFor(value, root);

    if (curr == nullptr){
        return nullptr;
    } else if (curr->right != nullptr){
        curr = curr->right;

        while (curr->left != nullptr){
            curr = curr->left;
        }
        return curr;
    }
    else {
        Node* parent = curr->parent;
        while (parent != nullptr && curr == parent->right) {
            curr = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

card card_list::getSuccessor(card value) const{
    Node* succ = getSuccessorNode(value);

    if(succ == nullptr){
        return {'0',"0"};
    } else {
        return succ->info;
    }
}

bool card_list::remove(card value){
    if (!contains(value)) {
        return false;
    }

    Node* delNode = getNodeFor(value, root);

    if (delNode->left == nullptr && delNode->right == nullptr) {
        if (delNode->parent == nullptr) {
            root = nullptr;
        } else if (delNode->parent->right == delNode) {
            delNode->parent->right = nullptr;
        } else {
            delNode->parent->left = nullptr;
        }
        delete delNode;
    }

    //1 child
    else if (delNode->left == nullptr || delNode->right == nullptr) {

    Node* child;

    if (delNode->right == nullptr) {
        child = delNode->left;
    } else {
        child = delNode->right;
    }

    if (delNode->parent == nullptr) {
        root = child;
        root->parent = nullptr;
    } 
    else {
        if (delNode->parent->right == delNode) {
            delNode->parent->right = child;
        } else {
            delNode->parent->left = child;
        }
        child->parent = delNode->parent;
    }
    
    delete delNode;
    }

    //2 children
    else {
        Node* successor = getSuccessorNode(delNode->info);
        card succ_val = successor->info;
        remove(succ_val);
        delNode->info = succ_val;
    }

    return true;
}