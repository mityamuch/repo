#pragma once

#include <string>

class Tex_convertible
{
public:
    virtual std::string convert() const = 0;
};