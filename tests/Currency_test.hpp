#include "BankSystem.hpp"
#include <gtest/gtest.h>

TEST(CurrencyTest, RegisterCurrenciesTest)
{
    Currency::RegisterCurrencies();
    EXPECT_EQ(Currency::s_Names[0], "BGN");
    EXPECT_EQ(Currency::s_Names[1], "EUR");
    EXPECT_EQ(Currency::s_Names[2], "USD");
    EXPECT_EQ(Currency::s_ConversionRates[0], 1.0);
    EXPECT_EQ(Currency::s_ConversionRates[1], 1.95);
    EXPECT_EQ(Currency::s_ConversionRates[2], 1.80);
}

TEST(CurrencyTest, AsBGNTest)
{
    auto cash = 100.00_BGN;
    auto convertedCash = Currency::AsBGN(cash);
    EXPECT_EQ(convertedCash.GetType(), Currency::Type::BGN);
    EXPECT_EQ(convertedCash.GetAmountAsDouble(), 100.0);
}

TEST(CurrencyTest, AsBGNTest2)
{
    auto cash = 100.00_EUR;
    auto convertedCash = Currency::AsBGN(cash);
    EXPECT_EQ(convertedCash.GetType(), Currency::Type::BGN);
    EXPECT_EQ(convertedCash.GetAmountAsDouble(), 100.0 * 1.95);
}

TEST(CurrencyTest, AsBGNTest3)
{
    auto cash = 100.00_USD;
    auto convertedCash = Currency::AsBGN(cash);
    EXPECT_EQ(convertedCash.GetType(), Currency::Type::BGN);
    EXPECT_EQ(convertedCash.GetAmountAsDouble(), 100.0 * 1.80);
}

TEST(CurrencyTest, GetNameTest)
{
    EXPECT_EQ(Currency::GetName(Currency::Type::BGN), "BGN");
    EXPECT_EQ(Currency::GetName(Currency::Type::EUR), "EUR");
    EXPECT_EQ(Currency::GetName(Currency::Type::USD), "USD");
}