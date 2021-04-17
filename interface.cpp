
#include <sstream>
#include "interface.hpp"
#include <limits>
#include <iostream>
using std::ostringstream;



float Interface::askBet(Drawable* drawable) const
{
    ostringstream oss;
    oss << "----------------------------" << '\n';
    oss << "How much do you want to bet?" << '\n';
    oss << drawable->draw() << '\n';
    std::cout << oss.str() << std::endl;
    float value = numberInput<float>();
    return value;
}


void Interface::noMoneyWarn(float balance) const
{
    std::cout << "Insufficient Funds " << "your balance is: " 
              << balance << '$' 
              << std::endl;
}

bool Interface::stayAsk(Drawable* drawable) const
{
    
    std::cout << "------------------\n"
              << drawable->draw() << '\n'
              << "Do you want to \n" 
              << "1. Hit \n"
              << "2. Stay \n"
              << std::endl;
    

    int choice = numberInput<int>([](int num) { return num > 0 && num < 2; });
    return choice < 2;
}


void Interface::showBust(Drawable* drawable, float value) const
{
    std::cout << "------------------\n"
              << drawable->draw()
              << ' '
              << "Busted with " 
              << value 
              << "$"
              << std::endl;
}


void Interface::showWin(Drawable* drawable, float value) const
{
    std::cout << "------------------\n"
              << drawable->draw()
              << ' '
              << "Win!!!  "
              << "Pot: " 
              << value 
              << "$"
              << std::endl;
}

void Interface::moneyBack(Drawable* drawable, float value) const
{
    std::cout << "------------------\n"
              << drawable->draw()
              << ' '
              << "Draw "
              << "Pot: " 
              << value 
              << "$"
              << std::endl;
}