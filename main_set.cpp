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
for (auto aliceIt = alice.begin(); aliceIt != alice.end();){

      auto bobIt = bob.begin();
      auto match = bob.find(*aliceIt);

      //check if Alice card in Bob hand
      if (match != bob.end()){
        cout << "Alice picked matching card " << (*aliceIt).get_suit() << " " <<  (*aliceIt).get_value() << endl;
        bob.erase(match);
        aliceIt = alice.erase(aliceIt);

        //bob's turn
        for(auto bobMatch = bobIt; bobMatch != bob.end();){
          //checking if Bob's card is in Alice's hand
          auto matchAlice = alice.find(*bobMatch);
          if (matchAlice != alice.end()){
            cout << "Bob picked matching card " << (*bobMatch).get_suit() << " " <<  (*bobMatch).get_value() << endl;
            alice.erase(matchAlice);
            bob.erase(bobMatch);
            break;
          }
          else {
            bobMatch++;
          }
        }
      }
      else {
        aliceIt++;
      }
      
      if (alice.empty() || bob.empty()) {
        break;
      }
    }
}