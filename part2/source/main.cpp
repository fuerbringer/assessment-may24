#include "endpoint.hpp"
#include "aggregatetradeparser.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

namespace
{
  const std::string DEFAULT_SYMBOL{"BTCUSDT"};

  std::string read_content_from_file(const std::string &fileName)
  {
    std::ifstream inputStream(fileName);
    std::string content((std::istreambuf_iterator<char>(inputStream)),
                        (std::istreambuf_iterator<char>()));
    return content;
  }

  std::string read_content_from_endpoint()
  {
    Endpoint endpoint{};
    return endpoint.get({"symbol=" + DEFAULT_SYMBOL});
  }
}

int main(const int argumentCount, const char *arguments[])
{
  std::string rawTradeData{};
  AggregateTradeParser parser{};
  if (argumentCount > 1)
  {
    // Read from file if one is provided
    rawTradeData = read_content_from_file(arguments[1]);
  }
  else
  {
    // Get from endpoint
    rawTradeData = read_content_from_endpoint();
  }

  if (rawTradeData.length() > 0)
  {
    const auto t_0{std::chrono::high_resolution_clock::now()};
    const auto trades{parser.string_to_trades(rawTradeData)};
    const auto t_1{std::chrono::high_resolution_clock::now()};
    const auto timeElapsed_mus{std::chrono::duration_cast<std::chrono::microseconds>(t_1 - t_0)};
    std::cout << "Parsed (" << trades.size() << ") trades in " << timeElapsed_mus.count() << "µs" << std::endl;
    std::cout << "First trade --------------------" << std::endl;
    std::cout << trades[0].to_string() << std::endl;
    std::cout << "Last trade --------------------" << std::endl;
    std::cout << trades[trades.size() - 1].to_string() << std::endl;
  }
  else
  {
    std::cout << "No trades were read in." << std::endl;
  }
  return 0;
}
