#pragma once

#include "endpointinterface.hpp"

class Endpoint : public EndpointInterface
{
public:
    Endpoint(const std::string baseUrl = DEFAULT_BASE_URL);
    std::string get(const std::vector<std::string> &parameters);

    static inline const std::string DEFAULT_BASE_URL{"https://testnet.binancefuture.com/fapi/v1/aggTrades"};
private:
    std::string m_baseUrl{};
};