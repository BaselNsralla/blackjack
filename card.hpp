#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "drawable.hpp"

using std::ostream;
using CardValue = size_t;

class Card : public Drawable
{
public:
    Card (CardValue value);
    CardValue getJackValue() const;
    friend std::ostream& operator<< (std::ostream& os, Card const& card);
protected:
    CardValue const value;  
};

std::ostream& operator<< (std::ostream& os, Card const& card);

void card_string(ostream& os, CardValue const& val, std::string&& shape);

struct HeartCard: public Card 
{
    using Card::Card;
    std::string draw() const override;
};

struct SpadeCard: public Card 
{
    using Card::Card;
    std::string draw() const override;

};

struct DiamondCard: public Card 
{
    using Card::Card;
    std::string draw() const override;
};

struct ClubCard: public Card 
{
    using Card::Card;
    std::string draw() const override;
};


