// card_list.h
// Author: Satvik Talchuru
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"

using namespace std;

class card_list {

 public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    card_list();                   // constructor
    ~card_list();                  // destructor
    bool insert(card value);     // insert value; return false if duplicate
    
    // 8 METHODS YOU MUST IMPLEMENT in intbst.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    bool contains(card value) const;  // true if value is in tree
    bool isEmpty() const;

    // THESE ARE HARDER! DO THESE LAST
    card getPredecessor(card value) const;       // returns the predecessor value of the given value or 0 if there is none
    card getSuccessor(card value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(card value);                    // deletes the Node containing the given value from the tree

    card findMax() const;
    card findMin() const;

 private:

    struct Node {
	card info;
	Node *left, *right, * parent;
	// useful constructor:
    Node(card v) : info(v), left(0), right(0), parent(0) { }
    };
    

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(card value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(card card, Node *n); // note overloading names for simplicity
    void printInOrder(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(card value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(card value) const; // returns the Node containing the predecessor of the given value
};

#endif


