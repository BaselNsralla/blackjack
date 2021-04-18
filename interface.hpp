#pragma once
#include <iostream>
#include "drawable.hpp"
#include <string>
#include <functional>
#include <vector>
#include <stdio.h>

using DrawableContainer = std::vector<Drawable*>;
using std::ostream;
using std::string;

struct Interface 
{
    void noMoneyWarn(float) const;
    float askBet(Drawable* drawable) const;
    bool stayAsk(Drawable* drawable) const;
    void showBust(Drawable* drawable, float value) const;
    void showWin(Drawable* drawable, float value) const;
    void moneyBack(Drawable* drawable, float value) const;
    void character(Drawable*);
    void roundStart();

private:
    template<typename T> 
    T numberInput(std::function<bool(T)>) const;
    
    template<typename T> 
    T numberInput() const;
};

template<typename T> // concept would have been better to make a number into a category of (int & float)
T Interface::numberInput(std::function<bool(T)> predicate) const 
{
    T num;
    while(true) 
    {
        std::cin >> num;
        if (!std::cin.fail() && predicate(num)) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number" << std::endl;
    }
    return num;
}

template<typename T> 
T Interface::numberInput() const 
{
    return numberInput<T>([](T num) { return true; });
}