#include <vector>
#include "player.hpp"
#include "dealer.hpp"
#include "interface.hpp"
#include <map>
#include <functional>
#include <ranges>
#include <algorithm>

static constexpr int BJ_WIN    = 21;
static constexpr int BJ_TARGET = 17;

using PlayerContainer = std::vector<Player*>;
//using std::views::filter;
using std::vector;

template<typename T>
vector<T> filter(const vector<T>& vec, std::function<bool(T)> predicate)
{
    vector<T> result;
    std::copy_if(vec.begin(), vec.end(), back_inserter(result), predicate);
    return result;
}


class Blackjack 
{
    PlayerContainer players;
    Dealer* dealer;
    Interface interface;
    std::map<intptr_t, float> round_bets; // Not the best id, but it works for now.
    void betPhase();
    void cardPhase();
    CardValue dealerCards();
    void bust(Player* player);
    void win(Player* player, bool bj = false);
    void draw(Player* player);
public:
    template<typename... Args>
    Blackjack(Interface&& interface, Dealer* dealer, Args... args): 
        interface{std::forward<Interface>(interface)},
        dealer{dealer},
        players{std::vector<Player*> { { args... } }}
    {}

    void play();
};

CardValue Blackjack::dealerCards() 
{
    CardValue dealerValue{dealer->calculate()};
    while(dealerValue < BJ_TARGET)
    {
        Card* card = dealer->deal();
        dealer->addCard(card);
        dealerValue = dealer->calculate();
        std::cout << dealer->draw() << std::endl;
    }
    return dealerValue;
}

void Blackjack::bust(Player* player) 
{
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showBust(player, roundBet);
    player->reset();
}

void Blackjack::win(Player* player, bool bj) 
{
    float multiplier = bj ? 2.5 : 2;
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    float pot = roundBet * multiplier;
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showWin(player, pot);
    player->increaseBalance(pot);
    player->reset();
}

void Blackjack::draw(Player* player) 
{
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showWin(player, roundBet);
    player->increaseBalance(roundBet);
    player->reset();
}



void Blackjack::cardPhase() {

    // i don't like this method, but will stick to it for now
    std::vector<Player*> prePick = players;
    std::vector<Player*> bust;
    std::vector<Player*> blackjack;

    // ======= Pre Choice =======
    for (int i = 0; i < 2; ++i) 
    {
        for (Player* player: prePick) 
        {
            Card* card = dealer->deal();
            player->addCard(card);
        }
        Card* card = dealer->deal();
        dealer->addCard(card);
    }
    
    // auto stayers = prePick | filter([&](Player* player) {
    //     CardValue currentVal = player->calculate();
    //     bool didBj   = currentVal == BJ_WIN;
    //     if(didBj) 
    //     {
    //         blackjack.push_back(player);
    //         return false;
    //     }
        
    //     bool didBust = false;
    //     while (!interface.stayAsk(player)) 
    //     {
    //         Card* card = dealer->deal();
    //         player->addCard(card);
    //         didBust = currentVal > BJ_WIN;
    //         if(didBust) 
    //         {
    //             bust.push_back(player);
    //         }
    //     } 

    //     return !(didBust || didBj);        
    // });

    auto stayers = filter<Player*>(prePick, [&](Player* player) {
        CardValue currentVal = player->calculate();
        bool didBj   = currentVal == BJ_WIN;
        if(didBj) 
        {
            blackjack.push_back(player);
            return false;
        }
        
        bool didBust = false;
        while (!interface.stayAsk(player)) 
        {
            Card* card = dealer->deal();
            player->addCard(card);
            didBust = currentVal > BJ_WIN;
            if(didBust) 
            {
                bust.push_back(player);
            }
        } 

        return !(didBust || didBj);        
    });

    CardValue dealerValue = dealerCards();

    std::for_each(stayers.begin(), stayers.end(), [&, this](Player* player) {
        CardValue playerValue = player->calculate();
        if (playerValue > dealerValue) 
        {
            this->win(player);
        } else if (playerValue < dealerValue)
        {
            this->bust(player);
        } else 
        {
            this->draw(player);
        }

    });

    std::for_each(bust.begin(), bust.end(), [this](Player* player) {
        this->bust(player);
    });

    std::for_each(blackjack.begin(), blackjack.end(), [this](Player* player) {
        this->win(player, true);
    });

}

void Blackjack::betPhase() 
{
    for (Player* player: players) 
    {
        float playerBalance = player->balance();
        if (playerBalance == 0) continue;

        float betMoney = interface.askBet(player);

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

void Blackjack::play()
{
    betPhase();
    cardPhase();
}