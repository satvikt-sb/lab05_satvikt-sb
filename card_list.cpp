// card_list.cpp
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"

#include <iostream>
using namespace std;

card_list::card_list() { 
    root = nullptr;
}
    
// destructor deletes all nodes
card_list::~card_list() {
    clear(root);
}

// recursive helper for destructor
void card_list::clear(Node *n) {
    if (!n){
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool card_list::insert(card value) {
    if(!root)
    {
        root = new Node(value);
        return true;
    }
    else
    {
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

// print tree data in-order, with helper
void card_list::printInOrder() const {
    printInOrder(root);
}
void card_list::printInOrder(Node *n) const {
    if(!n){return;}
    printInOrder(n->left);
    cout << (n->info).get_suit() << " " << (n->info).get_value() << endl;
    printInOrder(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
card_list::Node* card_list::getNodeFor(card value, Node* n) const{
    if(!n){
        return nullptr;
    }
    else if(n->info == value){
        return n;
    }
    else if(n->info > value){
        return getNodeFor(value, n->left);
    }
    else {
        return getNodeFor(value, n->right);
    }

}

// returns true if value is in the tree; false if not
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

// returns the predecessor value of the given value or 0 if there is none
card card_list::getPredecessor(card value) const{
    Node* pred = getPredecessorNode(value);

    if(pred == nullptr){
        return {'0',"0"};
    }
    else{
        return pred->info;
    }
}

// returns the Node containing the successor of the given value
card_list::Node* card_list::getSuccessorNode(card value) const{
    Node* curr = getNodeFor(value, root);

    if (curr == nullptr){
        return nullptr;
    }

    else if (curr->right != nullptr){
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

// returns the successor value of the given value or 0 if there is none
card card_list::getSuccessor(card value) const{
    Node* succ = getSuccessorNode(value);

    if(succ == nullptr){
        return {'0',"0"};
    }
    else{
        return succ->info;
    }
}


// Helper method to find the rightmost (maximum) node
card card_list::findMax() const {
    Node* node = root;
    while (node && node->right) {
        node = node->right;
    }
    return node->info;
}

// Helper method to find the leftmost (minimum) node
card card_list::findMin() const {
    Node* node = root;
    while (node && node->left) {
        node = node->left;
    }
    return node->info;
}
// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool card_list::remove(card value){
    if (contains(value) == false){
        return false;
    }

    Node* node_to_remove = getNodeFor(value,root);

    //if node has no children, leaf node
    if ( (node_to_remove->left == nullptr) && (node_to_remove->right == nullptr) ){

        if (node_to_remove->parent == nullptr){
            delete node_to_remove;
            root = nullptr;
        }

        else{ 

            if(node_to_remove->parent->right == node_to_remove){
                node_to_remove->parent->right = nullptr;
            }

            else 
            {
                node_to_remove->parent->left = nullptr;
            }
            delete node_to_remove;
        }

    }

    //if node has one child
    else if ((node_to_remove->left == nullptr) || (node_to_remove->right == nullptr)){

        card v('0',"0");
        Node* child = new Node(v);

        if (node_to_remove->right == nullptr){
            child = node_to_remove->left;
        }
        else {
            child = node_to_remove->right;
        }

        if(node_to_remove->parent == nullptr){
            root = child;
            root->parent = nullptr;
        }
        
        else{

            if (node_to_remove->parent->right == node_to_remove){
                node_to_remove->parent->right = child;
            }
            else {
                node_to_remove->parent->left = child;
            }

            child->parent = node_to_remove->parent;
        }

        delete node_to_remove;
    }

    // If node has two children
    else{
        Node* successor = getSuccessorNode(node_to_remove->info);

        card succ_val = successor->info;

        remove(succ_val);

        node_to_remove->info = succ_val;
    }
    

    return true;
}