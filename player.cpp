#include "player.hpp"

void Player::addCard(Card const* card) 
{   
    // I can accumulate right here to reduce the complexity by doing card->getJackValue() but std::execution::par looks so cool
    cards.push_back(card);
}

void Player::reset() 
{
    cards.clear();
}

CardValue Player::calculate() 
{
    return std::reduce(std::execution::par, cards.begin(), cards.end(), 0, [](int const init, Card const* const card) {
        return init + card->getJackValue();
    });
}