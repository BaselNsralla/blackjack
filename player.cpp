#include "player.hpp"

Player::Player(int money): money{money} {}

int Player::balance() const {
    return this->money;
}

void Player::addCard(Card const* card) 
{   
    // I can accumulate right here to reduce the complexity by doing card->getJackValue() but std::execution::par looks so cool
    cards.push_back(card);
}

void Player::reset() 
{
    cards.clear();
}

/*
  In case i would need to draw the player in different contextes or different ways
  I would create another .hpp file just for that
*/
std::string Player::draw() const 
{
    return "( ͡° ͜ʖ ͡°)"; // noramal state
}

CardValue Player::calculate() 
{
    return std::reduce(std::execution::par, cards.begin(), cards.end(), 0, [](int const init, Card const* const card) {
        return init + card->getJackValue();
    });
}

void Player::decreaseBalance(int money)
{
    this->money -= money;
}