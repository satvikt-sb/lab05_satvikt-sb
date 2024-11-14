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
  for (auto it = alice.begin(); it != alice.end();) {
        auto matchInBob = bob.find(*it);

        if (matchInBob != bob.end()) {
            cout << "Alice picked matching card " << it->get_suit() << " " << it->get_value() << endl;

            bob.erase(matchInBob);
            it = alice.erase(it);

            for (auto rator = bob.begin(); rator != bob.end(); ) {
                auto matchInAlice = alice.find(*rator);
     
                if (matchInAlice != alice.end()) {
                    cout << "Bob picked matching card " << rator->get_suit() << " " << rator->get_value() << endl;
    
                    alice.erase(matchInAlice);
                    rator = bob.erase(rator);
                    break;
                } else {
                    ++rator;  
                }
            }
        } else {
            ++it; 
        }

        if (alice.empty() || bob.empty()) {
            break;
        }
    }
}


