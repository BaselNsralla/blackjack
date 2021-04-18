#include "player.hpp"
#include <sstream>


Player::Player(float money): money{money} {}

float Player::balance() const {
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
    std::ostringstream oss;

    oss << face() << ' '; // normal state
    for (Card const* card: cards) {
        oss << card->draw() << ' ';
    }

    CardValue value = calculate();
    if (value != 0) 
    {
        oss << "(" << value << ")";
    }
    return oss.str();
}

std::string Player::info() const {
    std::ostringstream oss;
    oss << face() << balance() << '$';
    return oss.str();
}

std::string Player::face() const
{
    return "( ͡° ͜ʖ ͡°)";
}

CardValue Player::calculate() const
{
    return std::reduce(std::execution::par, cards.begin(), cards.end(), 0, [](int const init, Card const* const card) {
        return init + card->getJackValue();
    });
}

void Player::decreaseBalance(float money)
{
    this->money -= money;
}

void Player::increaseBalance(float money) 
{
    this->money += money;
}

