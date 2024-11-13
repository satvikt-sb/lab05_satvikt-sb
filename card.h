// card.h
// Author: Satvik Talchuru
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

class card{
    public:
        card(char suit, string value);
        pair <char,string> get_card(); 
        bool operator>(const card& comp_card) const;
        bool operator<(const card& comp_card) const;
        bool operator==(const card& comp_card) const;
        char get_suit() const;
        string get_value() const;
    private:
        pair <char,string> full_card;
};


#endif // CARD_H
