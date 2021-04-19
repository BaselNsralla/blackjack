
#include <sstream>
#include "interface.hpp"
#include <limits>
#include <vector>
#include <iostream>
using std::wostringstream;
using namespace std::string_literals;


float Interface::askBet(Drawable* drawable) const
{
    wostringstream oss;
    oss << L"----------------------------" << L'\n';
    oss << L"How much do you want to bet?" << L'\n';
    oss << drawable->draw();
    std::wcout << oss.str() << std::endl;
    float value = numberInput<float>();
    return value;
}


void Interface::noMoneyWarn(float balance) const
{
    std::wcout << L"Insufficient Funds " << "your balance is: " 
              << balance << L'$' 
              << std::endl;
}

bool Interface::stayAsk(Drawable* drawable) const
{
    
    std::wcout << "------------------\n"
              << drawable->draw() << '\n'
              << L"Do you want to \n" 
              << L"1. Hit \n"
              << L"2. Stay \n"
              << std::endl;
    

    int choice = numberInput<int>([](int num) { return num > 0 && num < 3; });
    return choice > 1;
}


void Interface::showBust(Drawable* drawable, float value) const
{
    std::wcout << drawable->draw()
              << L' '
              << L"Busted with " 
              << value 
              << L"$"
              << std::endl;
}


void Interface::showWin(Drawable* drawable, float value) const
{
    std::wcout << drawable->draw()
              << L' '
              << L"Win!!!  "
              << L"Pot: " 
              << value 
              << L"$"
              << std::endl;
}

void Interface::moneyBack(Drawable* drawable, float value) const
{
    std::wcout << drawable->draw()
              << L' '
              << L"Draw "
              << L"Pot: " 
              << value 
              << L"$"
              << std::endl;
}

void Interface::roundStart()
{
    std::wcout << L"\nPress Enter to start a new round...\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    getchar();

    std::wcout<< L"\033[2J\033[1;1H"; 
    std::wcout << L"\n=========New Round=========" << std::endl;
}

void Interface::characterInfo(Drawable* player)
{
    std::wcout << player->info();
}

void Interface::character(Drawable* player)
{
    std::wcout << player->draw();
}