#include "card.hpp"

void print_card(ostream& os, CardValue const& val, std::string&& shape) 
{
    switch (val)
    {
    case 1 : os << "Ace";
        break;
    case 11: os << "Jack";
        break;
    case 12: os << "Queen";
        break;
    case 13: os << "King";
        break;
    default:
        os << val;
    }
    os << " Of " << shape;
}

std::ostream& operator<< (std::ostream& os, Card const& card) 
{
    card.print(os); 
    return os;
}

CardValue Card::getJackValue() const 
{
    return value == 1 ? 11 : std::min<size_t>(10, value); 
}

Card::Card(CardValue value): value{value} {}

void HeartCard::print(ostream& os) const
{
    print_card(os, this->value, "♥");
}

void SpadeCard::print(ostream& os) const
{
    print_card(os, this->value, "♠");
}

void DiamondCard::print(ostream& os) const
{
    print_card(os, this->value, "♦");
}

void ClubCard::print(ostream& os) const
{
    print_card(os, this->value, "♣");
}

