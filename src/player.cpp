#include "player.hpp"
#include <sstream>
#include <iomanip>
using namespace std::string_literals;

Player::Player(float money, std::wstring illustration): money{money}, 
                                                        illustration{illustration} {}

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

    oss << std::setw(3) << std::left << std::fixed << appearance(); // normal state

    std::wostringstream cardsOss;
    for (Card const* card: cards) {
        cardsOss << card->draw() << L' ';
    }
    oss << std::setfill(L'.') << std::setw(45) << std::left << std::fixed << cardsOss.str();   
    
    CardValue value = calculate();
    std::wostringstream valOss;
    if (value != 0) 
    {
        std::wstring valStr = value == 21 && cards.size() == 2 ? L"BALCKJACK" : std::to_wstring(value);
        valOss << L"(" 
               << valStr
               << L")";
    }
    oss << std::setw(10) << std::left << std::fixed << valOss.str(); 
    return oss.str();
}

std::wstring Player::info() const {
    std::wostringstream oss;
    oss << appearance() << balance() << L"$\t";
    return oss.str();
}

std::wstring Player::appearance() const
{
    return illustration;
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

