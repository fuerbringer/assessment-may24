#pragma once

#include <string>
#include <vector>

struct Trade {
    int aggregateTradeId{};
    double price{};
    double quantity{};
    int firstTradeId{};
    int lastTradeId{};
    int timestamp{};
    bool buyerWasMaker{};
};

class AggregateTradeParser
{
public:
    std::vector<Trade> StringToTrades(const std::string& rawEndpointString);
};