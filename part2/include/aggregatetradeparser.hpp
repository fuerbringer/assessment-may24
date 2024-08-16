#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Trade {
    int aggregateTradeId{};
    double price{};
    double quantity{};
    int firstTradeId{};
    int lastTradeId{};
    long int timestamp{};
    bool buyerWasMaker{};

    std::string to_string() const {
        std::stringstream sstream; 
        sstream <<
        "Aggregate Trade ID: " << aggregateTradeId << std::endl << 
        "Price: " << price << std::endl <<
        "Quantity: " << quantity << std::endl <<
        "First trade ID: " << firstTradeId << std::endl <<
        "Last trade ID: " << lastTradeId << std::endl <<
        "Timestamp: " << timestamp << std::endl <<
        "Buyer was maker: " << buyerWasMaker << std::endl;
        return sstream.str();
    }
};

class AggregateTradeParser
{
public:
    std::vector<Trade> string_to_trades(const std::string& rawEndpointString);
};