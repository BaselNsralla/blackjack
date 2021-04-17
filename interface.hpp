#pragma once
#include <iostream>
#include "drawable.hpp"
#include <string>

using std::ostream;
using std::string;

struct Interface 
{
    void noMoneyWarn(int) const;
    int askBet(Drawable* drawable) const;
};