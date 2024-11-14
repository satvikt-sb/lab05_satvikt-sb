
#include "card_list.h"
#include "card.h"
#include <iostream>

using namespace std;


void testInsertAndFind() {
    card_list cards;
    card c1('c', "5"), c2('d', "10"), c3('h', "a");

    // Test insertions and findings
    bool passed = true;

    if (!cards.insert(c1) || !cards.contains(c1)) {
        cout << "testInsertAndFind failed on c1 insert/find" << endl;
        passed = false;
    }
    if (!cards.insert(c2) || !cards.contains(c2)) {
        cout << "testInsertAndFind failed on c2 insert/find" << endl;
        passed = false;
    }
    if (!cards.insert(c3) || !cards.contains(c3)) {
        cout << "testInsertAndFind failed on c3 insert/find" << endl;
        passed = false;
    }
    if (cards.contains(card('s', "2"))) {
        cout << "testInsertAndFind failed: found card not inserted" << endl;
        passed = false;
    }

    if (passed) cout << "testInsertAndFind passed!" << endl;
}

void testDelete() {
    card_list cards;
    card c1('c', "5"), c2('d', "10"), c3('h', "a");

    cards.insert(c1);
    cards.insert(c2);
    cards.insert(c3);

    bool passed = true;

    if (!cards.remove(c1) || cards.contains(c1)) {
        cout << "testDelete failed on c1 remove" << endl;
        passed = false;
    }
    if (!cards.remove(c2) || cards.contains(c2)) {
        cout << "testDelete failed on c2 remove" << endl;
        passed = false;
    }
    if (!cards.remove(c3) || cards.contains(c3)) {
        cout << "testDelete failed on c3 remove" << endl;
        passed = false;
    }

    if (passed) cout << "testDelete passed!" << endl;
}

void testSuccessor() {
    card_list cards;
    card c1('c', "5"), c2('d', "10"), c3('s', "3");

    cards.insert(c1);
    cards.insert(c2);
    cards.insert(c3);

    bool passed = true;

    if (cards.getSuccessor(c1).get_value() != "10") {
        cout << "testSuccessor failed for c1" << endl;
        passed = false;
    }
    if (cards.getSuccessor(c3).get_value() != "5") {
        cout << "testSuccessor failed for c3" << endl;
        passed = false;
    }
    if (cards.getSuccessor(c2).get_value() != "0") {  // No successor
        cout << "testSuccessor failed for c2" << endl;
        passed = false;
    }

    if (passed) cout << "testSuccessor passed!" << endl;
}

void testPredecessor() {
    card_list cards;
    card c1('c', "5"), c2('d', "10"), c3('s', "3");

    cards.insert(c1);
    cards.insert(c2);
    cards.insert(c3);

    bool passed = true;

    if (cards.getPredecessor(c1).get_value() != "3") {
        cout << "testPredecessor failed for c1" << endl;
        passed = false;
    }
    if (cards.getPredecessor(c2).get_value() != "5") {
        cout << "testPredecessor failed for c2" << endl;
        passed = false;
    }
    if (cards.getPredecessor(c3).get_value() != "0") {  // No predecessor
        cout << "testPredecessor failed for c3" << endl;
        passed = false;
    }

    if (passed) cout << "testPredecessor passed!" << endl;
}

void testFindMinAndMax() {
    card_list cards;
    card c1('c', "5"), c2('d', "10"), c3('s', "3");

    cards.insert(c1);
    cards.insert(c2);
    cards.insert(c3);

    bool passed = true;

    if (cards.findMin().get_value() != "3") {
        cout << "testFindMinAndMax failed on findMin" << endl;
        passed = false;
    }
    if (cards.findMax().get_value() != "10") {
        cout << "testFindMinAndMax failed on findMax" << endl;
        passed = false;
    }

    if (passed) cout << "testFindMinAndMax passed!" << endl;
}

int main() {
    testInsertAndFind();
    testDelete();
    testSuccessor();
    testPredecessor();
    testFindMinAndMax();

    cout << "All tests completed." << endl;
    return 0;
}