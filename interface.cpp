
#include <sstream>
#include "interface.hpp"
#include <limits>
#include <vector>
#include <iostream>
using std::ostringstream;



float Interface::askBet(Drawable* drawable) const
{
    ostringstream oss;
    oss << "----------------------------" << '\n';
    oss << "How much do you want to bet?" << '\n';
    oss << drawable->draw();
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
    

    int choice = numberInput<int>([](int num) { return num > 0 && num < 3; });
    return choice > 1;
}


void Interface::showBust(Drawable* drawable, float value) const
{
    std::cout << drawable->draw()
              << ' '
              << "Busted with " 
              << value 
              << "$"
              << std::endl;
}


void Interface::showWin(Drawable* drawable, float value) const
{
    std::cout << drawable->draw()
              << ' '
              << "Win!!!  "
              << "Pot: " 
              << value 
              << "$"
              << std::endl;
}

void Interface::moneyBack(Drawable* drawable, float value) const
{
    std::cout << drawable->draw()
              << ' '
              << "Draw "
              << "Pot: " 
              << value 
              << "$"
              << std::endl;
}

void Interface::roundStart()
{
    std::cout << "\nPress Enter to start a new round...\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    getchar();

    std::cout<< "\033[2J\033[1;1H"; 
    std::cout << "\n=========New Round=========" << std::endl;
}

void Interface::character(Drawable* drawable)
{
    std::cout << drawable->draw();
}