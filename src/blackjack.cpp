#include "blackjack.hpp"

void Blackjack::preparePhase()
{
    dealer->reset();
    interface.roundStart();
    for (auto player: players) 
    {
        player->reset();
        interface.characterInfo(player);
    }
    std::wcout << std::endl;
    stayer.clear();
    busted.clear();
    blackjacker.clear();
    prepick.clear();
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
            interface.noMoneyWarn(playerBalance);
            betMoney = interface.askBet(player);
        } 

        player->decreaseBalance(betMoney);
        round_bets[reinterpret_cast<intptr_t>(player)] = betMoney;
        prepick.push_back(player);
    }
}

void Blackjack::cardPhase() 
{
    initialCards();
    playerCards();
    dealerCards();
}

void Blackjack::resultPhase()
{
    CardValue dealerValue = dealer->calculate();
    std::for_each(stayer.begin(), stayer.end(), [&, this](Player* player) {
        CardValue playerValue = player->calculate();
        bool dealerBust = dealerValue > BJ_WIN || playerValue > dealerValue;
        if (dealerBust)  
        {
            win(player);
        } else if (playerValue < dealerValue) 
        {       
            bust(player);
        } else 
        {
            draw(player);
        }

    });

    std::for_each(busted.begin(), busted.end(), [this](Player* player) {
        this->bust(player);
    });

    std::for_each(blackjacker.begin(), blackjacker.end(), [this](Player* player) {
        this->win(player, true);
    });
}

void Blackjack::initialCards()
{
    // ======= Pre Choice =======
    for (int i = 0; i < 2; ++i) 
    {
        for (Player* player: prepick) 
        {
            Card* card = dealer->deal();
            player->addCard(card);
        }
        Card* card = dealer->deal();
        dealer->addCard(card);
    }
}

void Blackjack::dealerCards() 
{
    CardValue dealerValue{dealer->calculate()};
    while(dealerValue < BJ_TARGET)
    {
        Card* card = dealer->deal();
        dealer->addCard(card);
        dealerValue = dealer->calculate();
    }
    interface.character(dealer);
    std::wcout << std::endl;
}

bool Blackjack::hasBlackjack(Player* player) 
{
    CardValue currentVal = player->calculate();
    bool didBj   = currentVal == BJ_WIN;
        
    if(didBj) 
    {
        blackjacker.push_back(player);
    }

    return didBj;    
    
}

void Blackjack::playerCards() 
{
    stayer = filter<Player*>(prepick, [&](Player* player) {
        bool didBj = hasBlackjack(player);
        bool didBust = false;
        while (!didBj && !didBust && !interface.stayAsk(player)) 
        {
            Card* card = dealer->deal();
            player->addCard(card);
            didBj   =  hasBlackjack(player);
            didBust = player->calculate() > BJ_WIN;
            if(didBust) 
            {
                busted.push_back(player);
            }
        } 

        return !(didBust || didBj);        
    });
}

void Blackjack::win(Player* player, bool bj) 
{
    float multiplier = bj ? 2.5 : 2;
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    float pot = roundBet * multiplier;
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showWin(player, pot);
    player->increaseBalance(pot);
}

void Blackjack::bust(Player* player) 
{
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showBust(player, roundBet);
}

void Blackjack::draw(Player* player) 
{
    float roundBet = round_bets[reinterpret_cast<intptr_t>(player)];
    round_bets[reinterpret_cast<intptr_t>(player)] = 0;
    interface.showWin(player, roundBet);
    player->increaseBalance(roundBet);
}


void Blackjack::play()
{
    std::cin.putback ('\n'); // hack
    while(true)
    {
        preparePhase();
        betPhase();
        if (prepick.empty()) { break; }
        cardPhase();
        resultPhase();
    }
}