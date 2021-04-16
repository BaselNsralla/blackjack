#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using std::ostream;
using CardValue = size_t;

class Card 
{
public:
    Card (CardValue value);
    CardValue getJackValue() const;
    friend std::ostream& operator<< (std::ostream& os, Card const& card);
protected:
    CardValue const value;  
    virtual void print(ostream& os) const = 0;
};

std::ostream& operator<< (std::ostream& os, Card const& card);

void print_card(ostream& os, CardValue const& val, std::string&& shape);

struct HeartCard: public Card 
{
    using Card::Card;
private:
    void print(ostream& os) const override;
};

struct SpadeCard: public Card 
{
    using Card::Card;
private:
    void print(ostream& os) const override;
};

struct DiamondCard: public Card 
{
    using Card::Card;
private:
    void print(ostream& os) const override;
};

struct ClubCard: public Card 
{
    using Card::Card;
private:
    void print(ostream& os) const override;
};


