#include "deck.hpp"

Deck::Deck(bool shuffled)
{
    std::generate_n(cards.begin(),             13, SuccessorFunctor<HeartCard>());
    std::generate_n(next(cards.begin(), 13),   13, SuccessorFunctor<ClubCard>());
    std::generate_n(next(cards.begin(), 13*2), 13, SuccessorFunctor<SpadeCard>());
    std::generate_n(next(cards.begin(), 13*3), 13, SuccessorFunctor<DiamondCard>());
    
    if (shuffled) 
    {
        std::shuffle(cards.begin(), cards.end(), std::random_device());
    }

    // print the deck
    // for (auto& a: cards) 
    // {
    //     std::wcout << *a << std::endl;
    // }

}

Card* Deck::operator[](int index) const 
{
    return cards[index];
}

void Deck::rotateLeft()
{
    std::rotate(cards.begin(), cards.begin() + 1, cards.end());
}

Deck::~Deck() 
{
    for (Card* card: cards) 
    {
        delete card;
    }
}

