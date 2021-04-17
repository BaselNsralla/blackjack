#include "card.hpp"
#include <sstream>
// This return will be moved so no worries.
std::string card_string(CardValue const& val, std::string&& shape) 
{   
    std::ostringstream oss;
    switch (val)
    {
    case 1 : oss << "Ace";
        break;
    case 11: oss << "Jack";
        break;
    case 12: oss << "Queen";
        break;
    case 13: oss << "King";
        break;
    default:
        oss << val;
    }
    oss << " Of " << shape;
    return oss.str();
}

std::ostream& operator<< (std::ostream& os, Card const& card) 
{
    os << card.draw();
    return os;
}

CardValue Card::getJackValue() const 
{
    return value == 1 ? 11 : std::min<size_t>(10, value); 
}

Card::Card(CardValue value): value{value} {}

std::string HeartCard::draw() const
{
    return card_string(this->value, "♥");
}

std::string SpadeCard::draw() const
{
    return card_string(this->value, "♠");
}

std::string DiamondCard::draw() const
{
    return card_string(this->value, "♦");
}

std::string ClubCard::draw() const
{
    return card_string(this->value, "♣");
}

