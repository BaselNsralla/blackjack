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
    virtual std::wstring face() const;
    virtual std::wstring draw() const override;
    virtual std::wstring info() const override;
    CardValue calculate() const;
};