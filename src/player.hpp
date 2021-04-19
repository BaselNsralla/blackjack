#pragma once
#include "deck.hpp"
#include "card.hpp"
#include <execution>
#include <numeric>
#include "drawable.hpp"

class Player: public Drawable
{
    float money;
    std::wstring illustration;
    std::vector<Card const*> cards;
public:
    Player(float money, std::wstring illustration);
    void addCard(Card const* card);
    void reset();
    void decreaseBalance(float);
    void increaseBalance(float);
    float balance() const;
    virtual std::wstring appearance() const;
    virtual std::wstring draw() const override;
    virtual std::wstring info() const override;
    CardValue calculate() const;
};