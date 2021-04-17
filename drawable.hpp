#pragma once
#include <string>

struct Drawable 
{
    virtual std::string draw() const = 0;
};