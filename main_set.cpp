// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

struct DescendingOrder {
    bool operator()(const card& lhs, const card& rhs) const {
        return lhs > rhs; 
    }
};

void playgame(set<card> &alice, set<card, DescendingOrder> &bob);

int main(int argc, char* argv[]) {
  if(argc < 3) {
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

  set<card> alice;
  set<card, DescendingOrder> bob;

  //Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    char suit = line[0];
    string value = line.substr(2);
    card card(suit, value);
    alice.insert(card);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    char suit = line[0];
    string value = line.substr(2);
    card card(suit, value);
    bob.insert(card);
  }
  cardFile2.close();

  return 0;

  playgame(alice, bob);

  cout << endl;

  cout << "Alice's cards:" << endl;
  for (auto it : alice){
    cout << (it).get_suit() << " " << (it).get_value() << endl;
  }

  cout << endl;
  
  cout << "Bob's cards:" << endl;
  for (auto it = bob.rbegin(); it != bob.rend(); ++it){
    cout << (*it).get_suit() << " " << (*it).get_value() << endl;
  }
  
}


void playgame(set<card> &alice, set<card, DescendingOrder> &bob){
  bool aliceTurn = true;

  for (auto itAlice = alice.begin(), itBob = bob.begin(); !alice.empty() && !bob.empty();){
    if (aliceTurn){
      auto match = bob.find(*itAlice);
      if(match != bob.end()) {
        cout << "Alice picked matching card " << itAlice->get_suit() << " " <<  itAlice->get_value() << endl;
        bob.erase(match);
        itAlice = alice.erase(itAlice);
        aliceTurn = false;
      } else {
        ++itAlice;
        if(itAlice == alice.end()){
          break;
        }
      }
    }
    else {
      auto match2 = alice.find(*itBob);
      if (match2 != alice.end()){
        cout << "Bob picked matching card " << itBob->get_suit() << " " << itBob->get_value() << endl;
        alice.erase(match2);
        itBob = bob.erase(itBob);
        aliceTurn = true;
      } else {
        ++itBob;
        if (itBob == bob.end()){
          break;
        }
      }
    }
  }
}


