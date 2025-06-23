#include "BankSystem.hpp"
#include <gtest/gtest.h>

class BankSystemMock: public BankSystem
{
public:
    auto FindUserMock(std::string_view name) const -> std::expected<UserID, OperationError> { return FindUser(name); }

    auto GetUserBalanceMock(std::string_view name) const -> std::expected<CashT, OperationError>
    {
        return GetUserBalance(name);
    }

    auto GetUserStatusMock(std::string_view name) const -> std::expected<UserStatus, OperationError>
    {
        return GetUserStatus(name);
    }

    auto CheckPreconditionsMock(OpData& operation) -> std::expected<std::array<UserID, 2>, OperationError>
    {
        return CheckPreconditions(operation);
    }
};

TEST(BankSystem, Constructor)

{
    BankSystem bs;
    ASSERT_TRUE(Currency::GetConversionRate(Currency::Type::BGN) == 1.0);
    ASSERT_TRUE(Currency::GetConversionRate(Currency::Type::EUR) == 1.95);
    ASSERT_TRUE(Currency::GetConversionRate(Currency::Type::USD) == 1.80);

    ASSERT_EQ(Currency::GetName(Currency::Type::BGN), "BGN");
    ASSERT_EQ(Currency::GetName(Currency::Type::EUR), "EUR");
    ASSERT_EQ(Currency::GetName(Currency::Type::USD), "USD");
}

TEST(BankSystem, RegisterUser)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.FindUserMock("Pesho"); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value(), 0); }
}

TEST(BankSystem, RegisterUser2)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    registerResult = bs.RegisterUser("Pesho");
    ASSERT_FALSE(registerResult);
    if (auto result = bs.FindUserMock("Pesho"); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value(), 0); }
}

TEST(BankSystem, CashIN)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    registerResult = bs.RegisterUser("Ivan");
    ASSERT_TRUE(registerResult);
    registerResult = bs.RegisterUser("Gosho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.CashIn("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }
    if (auto result = bs.CashIn("Ivan", 10.00_EUR); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 19.50_BGN); }
    if (auto result = bs.CashIn("Gosho", 10.00_USD); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 18.00_BGN); }
}

TEST(BankSystem, CashOut)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.CashIn("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }
    if (auto result = bs.CashOut("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 0.00_BGN); }
}

TEST(BankSystem, CashOut2)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.CashIn("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }
    if (auto result = bs.CashOut("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 0.00_BGN); }
    if (auto result = bs.CashOut("Pesho", 10.00_BGN); result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.error(), BankSystem::OperationError::InsufficientFunds); }
}

TEST(BankSystem, Transfer)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    registerResult = bs.RegisterUser("Ivan");
    ASSERT_TRUE(registerResult);

    if (auto result = bs.CashIn("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }
    if (auto result = bs.CashIn("Ivan", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }

    if (auto result = bs.Transfer("Pesho", "Ivan", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else
    {
        ASSERT_EQ(result.value().balance, 0.00_BGN);
        if (auto balanceResult = bs.GetUserBalanceMock("Ivan"); !balanceResult.has_value()) { ASSERT_TRUE(false); }
        else { ASSERT_EQ(balanceResult.value(), 20.00_BGN); }
    }
}

TEST(BankSystem, Suspend)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.SuspendUser("Pesho"); !result.has_value()) { ASSERT_TRUE(false); }
    else
    {
        if (auto statusResult = bs.GetUserStatusMock("Pesho"); !statusResult.has_value()) { ASSERT_TRUE(false); }
        else { ASSERT_EQ(statusResult.value(), BankSystem::UserStatus::Suspended); }
    }
}

TEST(BankSystem, GetUserBalance)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    if (auto result = bs.CashIn("Pesho", 10.00_BGN); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value().balance, 10.00_BGN); }
    if (auto result = bs.GetUserBalanceMock("Pesho"); !result.has_value()) { ASSERT_TRUE(false); }
    else { ASSERT_EQ(result.value(), 10.00_BGN); }
}

TEST(BankSystem, GetUserBalance2)
{
    BankSystemMock bs;
    auto result = bs.GetUserBalanceMock("Ivan");
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserNotFound);
}

TEST(BankSystem, GetUserStatus)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    auto result = bs.GetUserStatusMock("Pesho");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), BankSystem::UserStatus::Active);
}

TEST(BankSystem, GetUserStatus2)
{
    BankSystemMock bs;
    auto registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    auto suspendResult = bs.SuspendUser("Pesho");
    ASSERT_TRUE(suspendResult.has_value());
    auto result = bs.GetUserStatusMock("Pesho");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), BankSystem::UserStatus::Suspended);
}

TEST(BankSystem, GetUserStatus3)
{
    BankSystemMock bs;
    auto result = bs.GetUserStatusMock("Ivan");
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserNotFound);
}

TEST(BankSystem, CheckPreconditions)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    BankSystem::OpData operation{BankSystem::OperationType::CashOut, {10.00_BGN}, {"Pesho"}};
    auto result = bs.CheckPreconditionsMock(operation);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::InsufficientFunds);
}

TEST(BankSystem, CheckPreconditions2)
{
    BankSystemMock bs;
    BankSystem::OpData operation{BankSystem::OperationType::CashOut, {10.00_BGN}, {"Pesho"}};
    auto result = bs.CheckPreconditionsMock(operation);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserNotFound);
}

TEST(BankSystem, CheckPreconditions3)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);

    auto suspendResult = bs.SuspendUser("Pesho");
    ASSERT_TRUE(suspendResult.has_value());

    BankSystem::OpData operation{BankSystem::OperationType::CashOut, {10.00_BGN}, {"Pesho"}};
    auto result = bs.CheckPreconditionsMock(operation);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserSuspended);

    BankSystem::OpData operation2{BankSystem::OperationType::Transfer, {10.00_BGN}, {"Pesho", "Ivan"}};
    result = bs.CheckPreconditionsMock(operation2);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserSuspended);
}

TEST(BankSystem, CheckPreconditions4)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);

    auto cashInResult = bs.CashIn("Pesho", 10.00_BGN);
    ASSERT_TRUE(cashInResult.has_value());

    BankSystem::OpData operation{BankSystem::OperationType::Transfer, {10.00_BGN}, {"Pesho", "Ivan"}};
    auto result = bs.CheckPreconditionsMock(operation);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UserNotFound);
}

TEST(BankSystem, CheckPreconditions5)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);

    auto cashInResult = bs.CashIn("Pesho", 10.00_BGN);
    ASSERT_TRUE(cashInResult.has_value());

    BankSystem::OpData operation{(BankSystem::OperationType)(0xDEADBEEF), {10.00_BGN}, {"Pesho", "Ivan"}};
    auto result = bs.CheckPreconditionsMock(operation);
    ASSERT_TRUE(!result.has_value());
    ASSERT_EQ(result.error(), BankSystem::OperationError::UnknownError);
}

TEST(BankSystem, PrintData)
{
    BankSystemMock bs;
    bool registerResult = bs.RegisterUser("Pesho");
    ASSERT_TRUE(registerResult);
    auto cashInResult = bs.CashIn("Pesho", 10.00_BGN);
    ASSERT_TRUE(cashInResult.has_value());
    bs.PrintData();
}