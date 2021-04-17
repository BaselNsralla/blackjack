#pragma once
#include "deck.hpp"
#include "card.hpp"
#include <execution>
#include <numeric>
#include "drawable.hpp"

class Player: public Drawable
{
    int money;
    std::vector<Card const*> cards;
public:
    Player(int money);
    void addCard(Card const* card);
    void reset();
    void decreaseBalance(int);
    int balance() const;
    std::string draw() const override;
    CardValue calculate();
};