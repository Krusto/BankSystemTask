#include "BankSystem_test.hpp"
#include "Cash_test.hpp"
#include "Currency_test.hpp"
#include "Log_test.hpp"
#include "User_test.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}