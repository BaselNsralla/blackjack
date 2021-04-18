#include "dealer.hpp"
#include <limits>
#include "card.hpp"
using namespace std::string_literals;

Dealer::Dealer(Deck& deck): deck{deck}, Player::Player(std::numeric_limits<float>::max()) {}

Card* Dealer::deal() 
{
    Card* card = deck[0];
    deck.rotateLeft();
    return card;
}


std::wstring Dealer::face() const
{
    return L"😒";//"😊";
}