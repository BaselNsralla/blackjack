#include "deck.hpp"
#include "dealer.hpp"
#include "player.hpp"
#include "blackjack.hpp"
#include "interface.hpp"
#include <iostream>


int main() {
    //Deck* deck_ptr = new Deck{false};
    //Deck& deck = *deck_ptr;

    Deck deck{true};
    Dealer dealer{deck};
    Player player(1337);
    player.addCard(deck[0]);
    player.addCard(deck[1]);
    Blackjack bj(Interface{}, &dealer, &player);
    bj.play();
    std::cout << player.calculate() << std::endl;
}