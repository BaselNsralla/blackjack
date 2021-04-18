#include "player.hpp"
#include <sstream>
#include <iomanip>
using namespace std::string_literals;

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
std::wstring Player::draw() const 
{   
    std::wostringstream oss;

    oss << std::setw(5) << std::left << std::fixed << face(); // normal state
    //oss.unsetf ( std::ios::showbase );

    std::wostringstream cardsOss;
    for (Card const* card: cards) {
        cardsOss << card->draw() << L' ';
    }
    oss << std::setfill(L'.') << std::setw(45) << std::left << std::fixed << cardsOss.str();   
    //oss << std::resetiosflags(std::ios::showbase);
    
    CardValue value = calculate();
    std::wostringstream valOss;
    if (value != 0) 
    {
        valOss << L"(" << value << L")";
    }
    oss << std::setw(5) << std::right << std::fixed << valOss.str(); 
    return oss.str();
}

std::wstring Player::info() const {
    std::wostringstream oss;
    oss << face() << balance() << L"$\t";
    return oss.str();
}

std::wstring Player::face() const
{
    return L"😒";
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

