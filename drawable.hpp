#pragma once
#include <string>

struct Drawable 
{
    virtual std::wstring draw() const = 0;
    virtual std::wstring info() const = 0;
};