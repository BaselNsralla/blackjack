#include "deck.hpp"
#include "dealer.hpp"
#include "player.hpp"
#include "blackjack.hpp"
#include "interface.hpp"
#include <iostream>
#include <string>
using namespace std::string_literals;

int main() 
{
    std::setlocale(LC_ALL, "");
    Deck deck{true};
    Dealer dealer{deck,   L"😷"};
    Player player(1337,   L"😍");
    Player player2(60000, L"😈");
    Blackjack blackjack(Interface{}, &dealer, &player, &player2);
    blackjack.play();
}