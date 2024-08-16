#pragma once

#include <string>
#include <vector>

class EndpointInterface
{
public:
    virtual std::string get(const std::vector<std::string> &parameters) = 0;
};