#pragma once

#include <string>
#include <vector>

struct Trade {
    int aggregateTradeId{};
    double price{};
    double quantity{};
    int firstTradeId{};
    int lastTradeId{};
    long int timestamp{};
    bool buyerWasMaker{};
};

class AggregateTradeParser
{
public:
    std::vector<Trade> string_to_trades(const std::string& rawEndpointString);
};