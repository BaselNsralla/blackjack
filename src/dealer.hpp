#pragma once
#include "player.hpp"

class Dealer: public Player 
{
private:
    Deck& deck;
public:
    Dealer(Deck& deck);
    Card* deal();
    std::wstring face() const override;
};
