
#include <sstream>
#include "interface.hpp"
#include <limits>
#include <iostream>
using std::ostringstream;

int Interface::askBet(Drawable* drawable) const
{
    ostringstream oss;
    oss << "----------------------------" << '\n';
    oss << "How much do you want to bet?" << '\n';
    oss << drawable->draw() << '\n';
    std::cout << oss.str() << std::endl;
    int num;
    while(true) 
    {
        std::cin >> num;
        if (!std::cin.fail()) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number" << std::endl;
    }

    return num;
}


void Interface::noMoneyWarn(int balance) const {
    std::cout << "Insufficient Funds " << "your balance is: " 
              << balance << '$' 
              << std::endl;
}