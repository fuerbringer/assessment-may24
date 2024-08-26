#include "aggregatetradeparser.hpp"
#include <algorithm>
#include <variant>

/*
(Comment)
Parser for the supplied format. Iterates over raw one-line string,
makes distinctions based on tokens and fast forwards over values after saving them.
For a JSON format, I'd consider using a fast implementation like rapidjson, but 
it depends on the needs and scope of the project.
*/

namespace
{
    enum class Token : const char
    {
        LIST_OPEN = '[',
        LIST_CLOSE = ']',
        OBJECT_OPEN = '{',
        OBJECT_CLOSE = '}',
        QUOTATION = '"',
        COLON = ':',
        SEPARATOR = ','
    };
    enum class ObjectType
    {
        INTEGER,
        DOUBLE,
        BOOLEAN
    };
    enum class State
    {
        KEY_AWAITING,
        VALUE_AWAITING,
    };
    struct Object
    {
        char key;
        std::variant<long int, double, bool> value;
    };
    void parse_key(State &state, std::string::const_iterator &iterator, Object &object, Trade &trade)
    {
        switch (state)
        {
        case State::KEY_AWAITING:
            iterator += 1;
            object.key = *iterator;
            iterator += 1;
            state = State::VALUE_AWAITING;
            break;
        default:
            break;
        }
    }
    void parse_value(State &state, std::string::const_iterator &iterator, std::string::const_iterator &end, Object &object, Trade &trade)
    {
        /*
        (Comment)
        Parsing of the various data types that appear in a value field.
        Could certainly be cleaned up further. Very state heavy.
        */
        switch (state)
        {
        case State::VALUE_AWAITING:
            iterator += 1;
            if (*iterator == static_cast<const char>(Token::QUOTATION))
            {
                iterator += 1;
                // float value
                const auto endOfDouble{std::find(iterator, end, static_cast<const char>(Token::QUOTATION))};
                std::string value{iterator, endOfDouble};
                object.value = std::stod(value.c_str());
                auto newEnd{iterator + value.length()};
                if (newEnd < end)
                {
                    iterator = newEnd; // forward
                }
            }
            else
            {
                switch (*iterator)
                {
                // booleans
                case 't':
                    object.value = true;
                    break;
                case 'f':
                    object.value = false;
                    break;

                default:
                    // integer, find where comma is
                    const auto endOfInteger{std::find(iterator, end, static_cast<const char>(Token::SEPARATOR))};
                    std::string value{iterator, endOfInteger};
                    object.value = std::stol(value.c_str());
                    auto newEnd{iterator + value.length()};
                    if (newEnd < end)
                    {
                        iterator = newEnd; // forward
                    }
                    break;
                }
            }
            state = State::KEY_AWAITING;
            break;
        default:
            break;
        }
    }
    void put_object_into_trade(Object &object, Trade &trade)
    {
        switch (object.key)
        {
        case 'a':
            trade.aggregateTradeId = std::get<0>(object.value);
            break;
        case 'p':
            trade.price = std::get<1>(object.value);
            break;
        case 'q':
            trade.quantity = std::get<1>(object.value);
            break;
        case 'f':
            trade.firstTradeId = std::get<0>(object.value);
            break;
        case 'l':
            trade.lastTradeId = std::get<0>(object.value);
            break;
        case 'T':
            trade.timestamp = std::get<0>(object.value);
            break;
        case 'm':
            trade.buyerWasMaker = std::get<2>(object.value);
            break;
        }
    }
}

std::string Trade::to_string() const
{
    std::stringstream sstream;
    sstream << "Aggregate Trade ID: " << aggregateTradeId << std::endl
            << "Price: " << price << std::endl
            << "Quantity: " << quantity << std::endl
            << "First trade ID: " << firstTradeId << std::endl
            << "Last trade ID: " << lastTradeId << std::endl
            << "Timestamp: " << timestamp << std::endl
            << "Buyer was maker: " << buyerWasMaker << std::endl;
    return sstream.str();
}

/*
(Comment)
The algorithmic complexity of this algorithm is O(n).
It "simply" iterates over the chars in the raw string from the endpoint without nested looping.
The state machine keeps track of what we're parsing.
*/
std::vector<Trade> AggregateTradeParser::string_to_trades(const std::string &rawEndpointString)
{
    std::vector<Trade> trades{};
    Trade trade{};
    State state{State::KEY_AWAITING};
    Object object{};
    auto end{rawEndpointString.end()};
    for (auto iterator{rawEndpointString.begin()}; iterator < end; iterator++)
    {
        const Token token{static_cast<const char>(*iterator)};
        switch (token)
        {
        case Token::LIST_OPEN:
        case Token::LIST_CLOSE:
            break;
        case Token::OBJECT_OPEN:
            trade = Trade();
            state = State::KEY_AWAITING;
            object = Object();
            break;
        case Token::OBJECT_CLOSE:
            trades.push_back(trade);
            break;
        case Token::QUOTATION:
            parse_key(state, iterator, object, trade);
            break;
        case Token::COLON:
            parse_value(state, iterator, end, object, trade);
            put_object_into_trade(object, trade);
            break;
        case Token::SEPARATOR:
            break;

        default:
            break;
        }
    }
    return trades;
}