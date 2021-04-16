#pragma once
#include "player.hpp"

class Dealer: public Player 
{
private:
    Deck const& deck;
public:
    Dealer(Deck const& deck);
};
