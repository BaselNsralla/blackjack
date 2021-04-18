#pragma once
#include <string>

struct Drawable 
{
    virtual std::string draw() const = 0;
    virtual std::string info() const = 0;
};