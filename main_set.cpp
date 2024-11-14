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

  for (std::set<card>::iterator it = alice.begin(); it != alice.end(); ++it) {
    cout << it->get_suit() << " " << it->get_value() << endl;
  }

  cout << endl;
  
  cout << "Bob's cards:" << endl;
  for (std::set<card>::reverse_iterator it = bob.rbegin(); it != bob.rend(); ++it) {
    cout << it->get_suit() << " " << it->get_value() << endl;
  }


  return 0; 
}


void playgame(set<card> &alice, set<card, DescendingOrder> &bob){
  set<card>::iterator aliceIt = alice.begin();
    while (aliceIt != alice.end()) {
       
        if (bob.find(*aliceIt) != bob.end()) {
            cout << "Alice picked matching card " << aliceIt->get_suit() << " " << aliceIt->get_value() << endl;

            bob.erase(*aliceIt);
            aliceIt = alice.erase(aliceIt); 
        } else {
            ++aliceIt; 
        }

        set<card, DescendingOrder>::iterator bobIt = bob.begin();
        while (bobIt != bob.end()) {
            if (alice.find(*bobIt) != alice.end()) {
                cout << "Bob picked matching card " << bobIt->get_suit() << " " << bobIt->get_value() << endl;

                alice.erase(*bobIt);
                bobIt = bob.erase(bobIt); 
            } else {
                ++bobIt; 
            }
        }
    }
}