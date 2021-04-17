#include "deck.hpp"
#include "dealer.hpp"
#include "player.hpp"
#include "blackjack.hpp"
#include "interface.hpp"
#include <iostream>


int main() 
{
    Deck deck{true};
    Dealer dealer{deck};
    Player player(1337);
    Blackjack blackjack(Interface{}, &dealer, &player);
    blackjack.play();
}