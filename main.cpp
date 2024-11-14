// This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
// Do not include set in this file

using namespace std;

void game(card_list &alice, card_list &bob);

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  card_list alice;
  card_list bob;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    card card(suit, value);
    alice.insert(card);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    card card(suit, value);
    bob.insert(card);
  }
  cardFile2.close();

  //running game
  game(alice, bob);

  cout << endl;
  //printing cards
  cout << "Alice's cards:" << endl;
  alice.printInOrder();
  cout << endl;
  cout << "Bob's cards:" << endl;
  bob.printInOrder();
  
  return 0;
}

void game(card_list &alice, card_list &bob){
    card aliceCard = alice.findMin();
    card bobCard = bob.findMax();

    while (!alice.isEmpty() && !bob.isEmpty()) {
        bool found = false;

        // Alice's turn
        while (bob.contains(aliceCard)) {
            cout << "Alice picked matching card " << (aliceCard).get_suit() << " " << (aliceCard).get_value() << endl;
            bob.remove(aliceCard);
            alice.remove(aliceCard);

            // Update aliceCard to new min
            if (!alice.isEmpty()) {
                aliceCard = alice.findMin();
            } else {
                aliceCard = card('0', "0");
            }

            // Update bobCard to new max
            if (!bob.isEmpty()) {
                bobCard = bob.findMax();
            } else {
                bobCard = card('0', "0");
            }
            
            found = true;
            break;
        }

        if (!found) {
            aliceCard = alice.getSuccessor(aliceCard);
            if (aliceCard == alice.findMax()){
              return;
            }
        }

        found = false;

        // Bob's turn
        while (alice.contains(bobCard)) {
            cout << "Bob picked matching card " << bobCard.get_suit() << " " << bobCard.get_value() << endl;
            alice.remove(bobCard);
            bob.remove(bobCard);

            // Update bobCard to new max
            if (!bob.isEmpty()) {
                bobCard = bob.findMax();
            } else {
                bobCard = card('0', "0");
            }

            // Update aliceCard to new min
            if (!alice.isEmpty()) {
                aliceCard = alice.findMin();
            } else {
                aliceCard = card('0', "0");
            }

            found = true;
            break;
        }

        if (!found) {
            bobCard = bob.getPredecessor(bobCard);
            if (bobCard == bob.findMin()){
              return;
            }
        }
      }
}