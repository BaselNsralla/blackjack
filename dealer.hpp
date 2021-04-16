#include "deck.hpp"
#include "card.hpp"
#include <execution>
#include <numeric>

class Player {
    std::vector<Card*> cards;
public:
    void addCard(Card* card) {
        cards.push_back(card);
    }

    void reset() {
        cards.clear();
    }

    CardValue calculate() {
        return std::reduce(std::execution::par, cards.begin(), cards.end(), 0, [](int const init, Card* const card) {
            return init + card->getJackValue();
        });
    }

};


class Dealer: public Player {
private:
    Deck const& deck;
public:
    Dealer(Deck const& deck);
};


Dealer::Dealer(Deck const& deck): deck{deck} 
{   


}