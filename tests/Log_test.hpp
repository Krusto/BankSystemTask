#include "Log.hpp"
#include <gtest/gtest.h>

TEST(LogTests, LogTest) { LOG("Test"); }

TEST(LogTests, LogTest2)
{
    int a = 5;
    double b = 5.5;
    double c = 5.123456;
    std::string d = "Test";

    LOG("{} {} {:.2f} {}", a, b, c, d);
}