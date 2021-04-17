#include "dealer.hpp"
#include <limits>

Dealer::Dealer(Deck const& deck): deck{deck}, Player::Player(std::numeric_limits<int>::max()) {}