#include "card_list.h"
#include "card.h"
#include <iostream>

using namespace std;

void testInsert() {
    card_list list;
    list.insert(card('h', "5"));
    cout << "Test Insert and Print:" << endl;
    list.printInOrder();
}

void testFindMin() {
    card_list list;
    list.insert(card('d', "3"));
    list.insert(card('c', "8"));
    cout << "Test Find Min:" << endl;
    cout << "Min card: " << list.findMin().get_suit() << " " << list.findMin().get_value() << endl;
}

void testFindMax() {
    card_list list;
    list.insert(card('h', "4"));
    list.insert(card('s', "10"));
    cout << "Test Find Max:" << endl;
    cout << "Max card: " << list.findMax().get_suit() << " " << list.findMax().get_value() << endl;
}

void testContains() {
    card_list list;
    list.insert(card('c', "7"));
    cout << "Test Contains:" << endl;
    cout << "Contains c 7? " << (list.contains(card('c', "7")) ? "Yes" : "No") << endl;
}

void testGetSuccessor() {
    card_list list;
    list.insert(card('c', "5"));
    list.insert(card('d', "9"));
    cout << "Test Get Successor:" << endl;
    cout << "Successor of c 5: " << list.getSuccessor(card('c', "5")).get_suit() << " " << list.getSuccessor(card('c', "5")).get_value() << endl;
}

void testGetPredecessor() {
    card_list list;
    list.insert(card('h', "6"));
    list.insert(card('d', "10"));
    cout << "Test Get Predecessor:" << endl;
    cout << "Predecessor of d 10: " << list.getPredecessor(card('d', "10")).get_suit() << " " << list.getPredecessor(card('d', "10")).get_value() << endl;
}

void testRemove() {
    card_list list;
    list.insert(card('s', "8"));
    list.insert(card('h', "3"));
    cout << "Test Remove:" << endl;
    list.printInOrder();
    list.remove(card('h', "3"));
    cout << "After removing h 3:" << endl;
    list.printInOrder();
}

void testIsEmpty() {
    card_list list;
    cout << "Test Is Empty:" << endl;
    cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    list.insert(card('d', "2"));
    cout << "Is list empty after insert? " << (list.isEmpty() ? "Yes" : "No") << endl;
}

int main() {
    testInsert();
    testFindMin();
    testFindMax();
    testContains();
    testGetSuccessor();
    testGetPredecessor();
    testRemove();
    testIsEmpty();
    return 0;
}
