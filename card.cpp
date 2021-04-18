#include "card.hpp"
#include <sstream>
#include <iomanip>
using namespace std::string_literals;

// This return will be moved so no worries.
std::wstring card_string(CardValue const& val, std::wstring&& shape) 
{   
    std::wostringstream oss;
    oss << L'|' << std::setw(2) << std::left << std::fixed;
    switch (val)
    {
    case 1 : oss << L"A";
        break;
    case 11: oss << L"J";
        break;
    case 12: oss << L"Q";
        break;
    case 13: oss << L"K";
        break;
    default:
        oss << val;
    }
    oss << std::resetiosflags(std::ios::showbase) << L" " << shape << L'|';
    return oss.str();
}

std::wostream& operator<< (std::wostream& os, Card const& card) 
{
    os << card.draw();
    return os;
}

std::wstring Card::info() const {
    std::wostringstream oss;
    oss << value;
    return oss.str();
}

CardValue Card::getJackValue() const 
{
    return value == 1 ? 11 : std::min<size_t>(10, value); 
}

Card::Card(CardValue value): value{value} {}

std::wstring HeartCard::draw() const
{
    return card_string(this->value, L"♥");
}

std::wstring SpadeCard::draw() const
{
    return card_string(this->value, L"♠");
}

std::wstring DiamondCard::draw() const
{
    return card_string(this->value, L"♦");
}

std::wstring ClubCard::draw() const
{
    return card_string(this->value, L"♣");
}

