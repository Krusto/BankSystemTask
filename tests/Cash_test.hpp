#include "BankSystem.hpp"
#include <gtest/gtest.h>

TEST(CashTests, DefaultConstructor)
{
    CashT cash;
    EXPECT_EQ(cash.GetType(), Currency::Type::BGN);
    EXPECT_EQ(cash.GetAmount().size(), 0);
}

TEST(CashTests, CashTest)
{
    CashT cash(Currency::Type::BGN, "100");
    EXPECT_EQ(cash.GetType(), Currency::Type::BGN);
    EXPECT_EQ(cash.GetAmount(), "100");
}

TEST(CashTests, GetType)
{
    CashT cash(Currency::Type::BGN, "100");
    EXPECT_EQ(cash.GetType(), Currency::Type::BGN);
}

TEST(CashTests, GetAmount)
{
    CashT cash(Currency::Type::BGN, "100");
    EXPECT_EQ(cash.GetAmount(), "100");
}

TEST(CashTests, GetAmountAsDouble)
{
    CashT cash(Currency::Type::BGN, "100");
    EXPECT_EQ(cash.GetAmountAsDouble(), 100.00);
}

TEST(CashTests, SetType)
{
    CashT cash(Currency::Type::BGN, "100");
    cash.SetType(Currency::Type::EUR);
    EXPECT_EQ(cash.GetType(), Currency::Type::EUR);
}

TEST(CashTests, SetAmount)
{
    CashT cash(Currency::Type::BGN, "100");
    cash.SetAmount("200");
    EXPECT_EQ(cash.GetAmount(), "200");
}

TEST(CashTests, Add)
{
    BankSystem bs;
    CashT cash1(Currency::Type::BGN, "100");
    CashT cash2(Currency::Type::BGN, "200");
    cash1.Add(cash2);
    EXPECT_EQ(cash1.GetAmount(), "300");
}

TEST(CashTests, Add2)
{
    BankSystem bs;
    CashT cash1(Currency::Type::BGN, "100");
    CashT cash2(Currency::Type::EUR, "100");
    cash1.Add(cash2);
    EXPECT_EQ(cash1.GetAmount(), "295");
}

TEST(CashTests, Sub)
{
    BankSystem bs;
    CashT cash1(Currency::Type::BGN, "100");
    CashT cash2(Currency::Type::BGN, "50");
    cash1.Sub(cash2);
    EXPECT_EQ(cash1.GetAmount(), "50");
}

TEST(CashTests, AsStr)
{
    CashT cash(Currency::Type::BGN, "100");
    EXPECT_EQ(cash.AsStr(100.00), "100");
}

TEST(CashTests, LessThan)
{
    CashT cash1(Currency::Type::BGN, "100");
    CashT cash2(Currency::Type::BGN, "200");
    EXPECT_TRUE(cash1 < cash2);
}

TEST(CashTests, GreaterThan)
{
    CashT cash1(Currency::Type::BGN, "200");
    CashT cash2(Currency::Type::BGN, "100");
    EXPECT_TRUE(cash1 > cash2);
}

TEST(CashTests, LabelBGN)
{
    CashT cash(100.00_BGN);
    EXPECT_EQ(cash.GetAmount(), "100");
}

TEST(CashTests, LabelEUR)
{
    CashT cash(100.00_EUR);
    EXPECT_EQ(cash.GetAmount(), "100");
}

TEST(CashTests, LabelUSD)
{
    CashT cash(100.00_USD);
    EXPECT_EQ(cash.GetAmount(), "100");
}