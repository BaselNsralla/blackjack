# Compile
```
g++ --std=c++20 main.cpp deck.cpp card.cpp player.cpp dealer.cpp interface.cpp blackjack.cpp
```

### TODO
- Ace adaptive value   
    CardValue (int|int): Possible implementation:
    CardValue x + CardValue y = CardValue (x.first + y.first | x.second + y.second)
- Blackjack only with A+10