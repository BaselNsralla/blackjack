#pragma once
#include "deck.hpp"
#include "card.hpp"
#include <execution>
#include <numeric>

class Player 
{
    std::vector<Card const*> cards;
public:
    void addCard(Card const* card);
    void reset();
    CardValue calculate();
};