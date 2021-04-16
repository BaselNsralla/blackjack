
#include <vector>
#include "player.hpp"
#include "dealer.hpp"
#include "interface.hpp"
using PlayerContainer = std::vector<Player*>;

class Blackjack 
{
    PlayerContainer players;
    Dealer* dealer;
    Interface interface;

public:
    template<typename... Args>
    Blackjack(Interface&& interface, Dealer* dealer, Args... args): 
        interface{std::forward<Interface>(interface)},
        dealer{dealer},
        players{std::vector<Player*> { { args... } }}
    {}

    void play();

};

void Blackjack::play() {
    for (Player* player: players) 
    {

    }

}