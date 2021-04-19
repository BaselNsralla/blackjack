#pragma once
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
    PlayerContainer prepick;
    PlayerContainer stayer;
    PlayerContainer busted;
    PlayerContainer blackjacker;
    std::map<intptr_t, float> round_bets; // Not the best id, but it works for now.
    
    // Game phases
    void preparePhase();
    void betPhase();
    void cardPhase();
    void resultPhase();
    
    // Card dealing
    void initialCards();
    void dealerCards();
    void playerCards();

    // Result Aux
    void bust(Player* player);
    void win(Player* player, bool bj = false);
    void draw(Player* player);

    // Card Aux
    bool hasBlackjack(Player* player); 

public:
    template<typename... Args>
    Blackjack(Interface&& interface, Dealer* dealer, Args... args): 
        interface{std::forward<Interface>(interface)},
        dealer{dealer},
        players{std::vector<Player*> { { args... } }}
    {}

    void play();
};
