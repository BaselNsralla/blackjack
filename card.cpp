#include "card.hpp"
#include <sstream>
// This return will be moved so no worries.
std::string card_string(CardValue const& val, std::string&& shape) 
{   
    std::ostringstream oss;
    oss << '|';
    switch (val)
    {
    case 1 : oss << "A";
        break;
    case 11: oss << "J";
        break;
    case 12: oss << "Q";
        break;
    case 13: oss << "K";
        break;
    default:
        oss << val;
    }
    oss << " " << shape << '|';
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

