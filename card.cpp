// card.cpp
// Author: Satvik Talchuru
// Implementation of the classes defined in card.h

#include "card.h"
#include <iostream>
#include <map>
#include <string>

map<char, int> suitOrder = {
        {'c', 1}, {'d', 2}, {'s', 3}, {'h', 4},{'0', 0} // Clubs, Diamonds, Spades, Hearts
    };

map<string, int> valueOrder = {
    {"a", 1}, {"1", 2}, {"2", 3}, {"3", 4}, {"4", 5},
    {"5", 6}, {"6", 7}, {"7", 8}, {"8", 9}, {"9", 10},
    {"10", 11}, {"j", 12}, {"q", 13}, {"k", 14}, {"0",0}
};

card::card(char suit, string value){
    final_card.first = suit;
    final_card.second = value;
}

char card::get_suit() const{
    return this->final_card.first;
}

string card::get_value() const{
    return this->final_card.second;
}

bool card::operator==(const card& comp_card) const{

    return suitOrder.at(get_suit()) == suitOrder.at(comp_card.get_suit()) &&
               valueOrder.at(get_value()) == valueOrder.at(comp_card.get_value());
}

bool card::operator<(const card& comp_card) const{


    // First compare suits
    if (suitOrder.at(this->get_suit()) < suitOrder.at(comp_card.get_suit())) {
        return true;
    } else if (suitOrder.at(this->get_suit()) > suitOrder.at(comp_card.get_suit())) {
        return false;
    }

    // If suits are equal, compare values
    return valueOrder.at(this->get_value()) < valueOrder.at(comp_card.get_value());
}

bool card::operator>(const card& comp_card) const{


    // First compare suits
    if (suitOrder.at(this->get_suit()) > suitOrder.at(comp_card.get_suit())) {
        return true;
    } else if (suitOrder.at(this->get_suit()) < suitOrder.at(comp_card.get_suit())) {
        return false;
    }

    // If suits are equal, compare values
    return valueOrder.at(this->get_value()) > valueOrder.at(comp_card.get_value());
}

