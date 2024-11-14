// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

//Order set from greatest to leastest; will be Bob
struct DescendingOrder {
    bool operator()(const card& lhs, const card& rhs) const {
        return lhs > rhs; 
    }
};

void playgame(set<card> &alice, set<card, DescendingOrder> &bob);

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file/s " << endl;
    return 1;
  }

  set<card> alice; 
  set<card, DescendingOrder> bob;

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

  return 0; 
}


void playgame(set<card> &alice, set<card, DescendingOrder> &bob){

  for (auto aliceIt = alice.begin(); aliceIt != alice.end(); ) {
        auto bobMatch = bob.find(*aliceIt);
        if (bobMatch != bob.end()) {
            cout << "Alice picked matching card " << aliceIt->get_suit() << " " << aliceIt->get_value() << endl;
            bob.erase(bobMatch);
            aliceIt = alice.erase(aliceIt); // Update Alice's iterator
        } else {
            ++aliceIt; // Next card
        }
       
        if (alice.empty() || bob.empty()){
          break;
        }

        // Bob's turn: iterate through his hand from the largest card
        for (auto bobIt = bob.begin(); bobIt != bob.end(); ) {
            // Check if Bob's current card is in Alice's hand
            auto aliceMatch = alice.find(*bobIt);
            if (aliceMatch != alice.end()) {
                // Bob picks a matching card
                cout << "Bob picked matching card " << bobIt->get_suit() << " " << bobIt->get_value() << endl;

                // Remove matching card from both Alice and Bob's hands
                alice.erase(aliceMatch);
                bobIt = bob.erase(bobIt); // Update Bob's iterator after removal
                break; // End Bob's turn after finding a match
            } else {
                ++bobIt; // 
            }
        }

        // 
          if (alice.empty() || bob.empty()){
            break;
          }
      }
}