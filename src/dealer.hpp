#pragma once
#include "player.hpp"

class Dealer: public Player 
{
private:
    Deck& deck;
public:
    Dealer(Deck& deck, std::wstring);
    Card* deal();
    std::wstring appearance() const override;
};
