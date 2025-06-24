#include "BankSystem.hpp"
#include <gtest/gtest.h>

TEST(UserTests, TestInit)
{
    User user("Ivan", 1);
    EXPECT_EQ(user.GetName(), "Ivan");
    EXPECT_EQ(user.GetID(), 1);
}

TEST(UserTests, SetID)
{
    User user("Ivan", 1);
    user.SetID(2);
    EXPECT_EQ(user.GetID(), 2);
}

TEST(UserTests, GetID)
{
    User user("Ivan", 1);
    EXPECT_EQ(user.GetID(), 1);
}

TEST(UserTests, GetName)
{
    User user("Ivan", 1);
    EXPECT_EQ(user.GetName(), "Ivan");
}

TEST(UserTests, SetName)
{
    User user("Ivan", 1);
    user.SetName("Pesho");
    EXPECT_EQ(user.GetName(), "Pesho");
}
