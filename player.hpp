#pragma once
#include "deck.hpp"
#include "card.hpp"
#include <execution>
#include <numeric>
#include "drawable.hpp"

class Player: public Drawable
{
    float money;
    std::vector<Card const*> cards;
public:
    Player(float money);
    void addCard(Card const* card);
    void reset();
    void decreaseBalance(float);
    void increaseBalance(float);
    float balance() const;
    virtual std::string face() const;
    virtual std::string draw() const override;
    CardValue calculate() const;
};