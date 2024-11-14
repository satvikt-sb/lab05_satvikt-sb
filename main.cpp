// This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
// Do not include set in this file

using namespace std;

void playgame(card_list &alice, card_list &bob);

int main(int argc, char* argv[]) {
  if(argc < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argv[1]);
  ifstream cardFile2(argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << argv[2];
    return 1;
  }

  card_list alice;
  card_list bob;

  //Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    char suit = line[0];
    string value = line.substr(2);
    alice.insert(card(suit, value));
  }
  cardFile1.close();


  while (getline(cardFile2, line) && (line.length() > 0)) {
    char suit = line[0];
    string value = line.substr(2);
    bob.insert(card(suit, value));
  }
  cardFile2.close();

  playgame(alice, bob);
  cout << endl;

  //printing cards
  cout << "Alice's cards:" << endl;
  alice.printInOrder();
  cout << endl;
  cout << "Bob's cards:" << endl;
  bob.printInOrder();
  
  return 0;
}

void playgame(card_list &alice, card_list &bob){
  bool finished = false;
  card aliceCard = alice.findMin();
  card bobCard = bob.findMax();

  while(!finished){
    finished = true;

    //Alice's turn
    while(true){
      if(bob.contains(aliceCard)){
        cout << "Alice picked matching card " << aliceCard.get_suit() << " " << aliceCard.get_value() << endl;
        bob.remove(aliceCard);
        alice.remove(bobCard);
        bobCard = bob.findMax();
        finished = false;
        break;
      } else {
        aliceCard = alice.getSuccessor(aliceCard);
      }
      if (aliceCard == alice.findMax()) {
        return;
      }
    } 

    while (true) {
      if (alice.contains(bobCard)) {
        cout << "Bob picked matching card " << bobCard.get_suit() << " " << bobCard.get_value() << endl;
        alice.remove(aliceCard); 
        bob.remove(bobCard);   
        aliceCard = alice.findMin(); 
        finished = false;     
        break;   
      } else {
        bobCard = bob.getPredecessor(bobCard); 
      }
        if (bobCard == bob.findMin()) {
          return;
    }
    }

  }
}
