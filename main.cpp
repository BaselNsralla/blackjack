#include "deck.hpp"
#include "dealer.hpp"
#include "player.hpp"
#include "blackjack.hpp"
#include "interface.hpp"
#include <iostream>


int main() {
    //Deck* deck_ptr = new Deck{false};
    //Deck& deck = *deck_ptr;

    Deck deck{false};
    Dealer dealer{deck};
    Player player;
    player.addCard(deck[0]);
    player.addCard(deck[1]);
    Blackjack bj(Interface{}, &dealer, &player);
    std::cout << player.calculate() << std::endl;
}