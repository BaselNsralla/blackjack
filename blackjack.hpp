#include <vector>
#include "player.hpp"
#include "dealer.hpp"
#include "interface.hpp"
#include <map>

using PlayerContainer = std::vector<Player*>;

class Blackjack 
{
    PlayerContainer players;
    Dealer* dealer;
    Interface interface;
    std::map<intptr_t, int> round_bets; // Not the best id, but it works for now.

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
        int playerBalance = player->balance();
        if (playerBalance == 0) continue;

        int betMoney = interface.askBet(player);
        
        while(betMoney > playerBalance)
        {
            std::cout << "VA? " << std::endl;
            interface.noMoneyWarn(playerBalance);
            betMoney = interface.askBet(player);

        } 

        player->decreaseBalance(betMoney);
        round_bets[reinterpret_cast<intptr_t>(player)] = betMoney;
    }




}