#include <gtest/gtest.h>
#include "aggregatetradeparser.hpp"

namespace
{
  const auto VALID_SINGLE_TRADE{"[{\"a\":173264206,\"p\":\"57475.10\",\"q\":\"0.017\",\"f\":288456246,\"l\":288456246,\"T\":1723827137604,\"m\":false}"};
}

bool operator==(const Trade left, const Trade right)
{
  return left.aggregateTradeId == right.aggregateTradeId &&
         left.price == right.price &&
         left.quantity == right.quantity &&
         left.firstTradeId == right.firstTradeId &&
         left.lastTradeId == right.lastTradeId &&
         left.timestamp == right.timestamp &&
         left.buyerWasMaker == right.buyerWasMaker;
}

/*
(Comment)
Class AggregateTradeParser was implemented test driven and incrementally with each test. 
Test bodies conform to AAA pattern.
*/

TEST(AggregateTradeParserTest, EmptyRawStringReturnsEmptyListOfTrades)
{
  AggregateTradeParser parser{};

  const auto emptyString{""};
  const auto result{parser.string_to_trades(emptyString)};

  EXPECT_EQ(0, result.size());
}

TEST(AggregateTradeParserTest, RawStringContainingOneIdKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingTwoKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\"}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingThreeKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\"}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingFourKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  expectedTrade.firstTradeId = 27781;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingFiveKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  expectedTrade.firstTradeId = 27781;
  expectedTrade.lastTradeId = 22782;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingSixKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  expectedTrade.firstTradeId = 27781;
  expectedTrade.lastTradeId = 22782;
  expectedTrade.timestamp = 1498793709153;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingBooleanKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153,\"m\":true}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  expectedTrade.firstTradeId = 27781;
  expectedTrade.lastTradeId = 22782;
  expectedTrade.timestamp = 1498793709153;
  expectedTrade.buyerWasMaker = true;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingCommaAfterLastKeyValueTradeReturnsCorrectTradeObject)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153,\"m\":true,}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTrade{result[0]};
  Trade expectedTrade{};
  expectedTrade.aggregateTradeId = 173264676;
  expectedTrade.price = 0.01633102;
  expectedTrade.quantity = 4.70443515;
  expectedTrade.firstTradeId = 27781;
  expectedTrade.lastTradeId = 22782;
  expectedTrade.timestamp = 1498793709153;
  expectedTrade.buyerWasMaker = true;
  EXPECT_EQ(expectedTrade, actualTrade);
}

TEST(AggregateTradeParserTest, RawStringContainingTwoTradesReturnsTwoTrades)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153,\"m\":true},{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153,\"m\":true}]"};
  const auto result{parser.string_to_trades(rawString)};

  EXPECT_EQ(2, result.size());
}

TEST(AggregateTradeParserTest, RawStringContainingTwoTradesReturnsTwoCorrectContents)
{
  AggregateTradeParser parser{};

  const std::string rawString{"[{\"a\":173264676,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":27781,\"l\":22782,\"T\":1498793709153,\"m\":true},{\"a\":123,\"p\":\"0.01633102\",\"q\":\"4.70443515\",\"f\":456,\"l\":78910,\"T\":1498000000001,\"m\":true}]"};
  const auto result{parser.string_to_trades(rawString)};

  const auto actualTradeOne{result[0]};
  const auto actualTradeTwo{result[1]};
  Trade expectedTradeOne{};
  expectedTradeOne.aggregateTradeId = 173264676;
  expectedTradeOne.price = 0.01633102;
  expectedTradeOne.quantity = 4.70443515;
  expectedTradeOne.firstTradeId = 27781;
  expectedTradeOne.lastTradeId = 22782;
  expectedTradeOne.timestamp = 1498793709153;
  expectedTradeOne.buyerWasMaker = true;
  Trade expectedTradeTwo{};
  expectedTradeTwo.aggregateTradeId = 123;
  expectedTradeTwo.price = 0.01633102;
  expectedTradeTwo.quantity = 4.70443515;
  expectedTradeTwo.firstTradeId = 456;
  expectedTradeTwo.lastTradeId = 78910;
  expectedTradeTwo.timestamp = 1498000000001;
  expectedTradeTwo.buyerWasMaker = true;
  EXPECT_EQ(expectedTradeOne, actualTradeOne);
}