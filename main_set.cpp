// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

//to order set from greatest to leasr
struct CompareCardsDescending {
    bool operator()(const card& lhs, const card& rhs) const {
        return lhs > rhs; 
    }
};

void game(set<card> &alice, set<card, CompareCardsDescending> &bob);

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

  set<card> alice; //least to greatest
  set<card, CompareCardsDescending> bob; //greatest to least

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

  //printing remaining cards
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






void game(set<card> &alice, set<card, CompareCardsDescending> &bob){

    for (auto it = alice.begin(); it != alice.end();){

      auto bobby = bob.begin();
      
      auto match = bob.find(*it);

      //checking if Alice's card is in Bob's hand
      if ( match != bob.end() ){
        
        cout << "Alice picked matching card " << (*it).get_suit() << " " <<  (*it).get_value() << endl;
        
        bob.erase(match);
        it = alice.erase(it);

        //bob's turn
        for(auto rator = bobby; rator != bob.end();){
          //checking if Bob's card is in Alice's hand
          auto matchAlice = alice.find(*rator);

          if (matchAlice != alice.end()){

            cout << "Bob picked matching card " << (*rator).get_suit() << " " <<  (*rator).get_value() << endl;

            alice.erase(matchAlice);
            bob.erase(rator);
          
            break;
          }
          else {
            rator++;
          }
        }
      }
      else {
        it++;
      }

      if (alice.empty() || bob.empty()) {
        break;
      }
    }
}


