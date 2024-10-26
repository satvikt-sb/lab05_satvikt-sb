// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

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

  //Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {

  }

  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {

  }

  cardFile2.close();

  return 0;
}
