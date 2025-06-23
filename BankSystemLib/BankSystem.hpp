
#pragma once
#include "Cash.hpp"
#include "User.hpp"
#include <array>
#include <expected>
#include <map>
#include <string_view>

class BankSystem
{
public:
    BankSystem();
    ~BankSystem();

public:
    using UserID = size_t;
    enum class OperationError : size_t
    {
        Success = 0,
        UserNotFound,
        UserSuspended,
        InsufficientFunds,
        InternalError,
        UnknownError
    };
    enum class OperationType : size_t
    {
        CashIn = 0,
        CashOut,
        Transfer,
        Suspend,
    };

    struct OperationResult {
        CashT balance;
    };

    struct OpData {
        OperationType type;
        std::array<CashT, 2> amounts;
        std::array<std::string_view, 2> users;
    };

    enum class UserStatus : size_t
    {
        Suspended = 0,
        Active
    };

    struct UserData {
        UserStatus status;
        CashT balance;
    };

public:
    using OpResult = std::expected<OperationResult, OperationError>;

    auto RegisterUser(std::string_view name) -> bool;
    auto CashIn(std::string_view name, CashT amount) -> OpResult;
    auto CashOut(std::string_view name, CashT amount) -> OpResult;
    auto Transfer(std::string_view from, std::string_view to, CashT amount) -> OpResult;
    auto SuspendUser(std::string_view name) -> OpResult;
    auto PrintData() -> void;

protected:
    auto HandleOperation(OpData operation) -> OpResult;
    auto CheckPreconditions(OpData& operation) -> std::expected<std::array<UserID, 2>, OperationError>;
    auto FindUser(std::string_view name) const -> std::expected<UserID, OperationError>;
    auto GetUserBalance(std::string_view name) const -> std::expected<CashT, OperationError>;
    auto GetUserStatus(std::string_view name) const -> std::expected<UserStatus, OperationError>;

protected:
    std::map<UserID, User> m_Users;
    std::map<UserID, UserData> m_UsersData;
};