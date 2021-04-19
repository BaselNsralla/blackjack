#pragma once
#include "card.hpp"
#include <vector>
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <algorithm>
#include <random>

using std::next;
using CardVector = typename std::array<Card*, 52>;

template<typename CardType>
struct SuccessorFunctor 
{
    CardValue i{1};
    Card* operator()();
};

class Deck 
{
    CardVector cards;
public:
    Deck(bool shuffled);
    ~Deck();
    Card* operator[](int index) const;
    void rotateLeft();
};

template<typename CardType>
Card* SuccessorFunctor<CardType>::operator()() 
{
    if (i > 13) { i = 0; }
    return new CardType(i++);
}