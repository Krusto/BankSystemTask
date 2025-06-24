#include "BankSystem.hpp"
#include "Log.hpp"
#include <cassert>

BankSystem::BankSystem() { Currency::RegisterCurrencies(); }

BankSystem::~BankSystem()
{
    m_Users.clear();
    m_UsersData.clear();
    UserFactory::Destroy();
}

auto BankSystem::RegisterUser(std::string_view name) -> bool
{
    auto result = FindUser(name);
    if (result.has_value()) return false;

    auto user = UserFactory::GetInstance()->CreateUser(name);

    m_Users.emplace(user.GetID(), std::move(user));
    m_UsersData.emplace(user.GetID(), UserData{UserStatus::Active, {}});
    return true;
}

auto BankSystem::CashIn(std::string_view name, CashT amount) -> BankSystem::OpResult
{
    return HandleOperation({OperationType::CashIn, {amount, {}}, {name, {}}});
}

auto BankSystem::CashOut(std::string_view name, CashT amount) -> BankSystem::OpResult
{
    return HandleOperation({OperationType::CashOut, {amount, {}}, {name, {}}});
}

auto BankSystem::Transfer(std::string_view from, std::string_view to, CashT amount) -> BankSystem::OpResult
{
    return HandleOperation({OperationType::Transfer, {amount, {}}, {from, to}});
}

auto BankSystem::SuspendUser(std::string_view name) -> BankSystem::OpResult
{
    return HandleOperation({OperationType::Suspend, {}, {name, {}}});
}

auto BankSystem::HandleOperation(OpData operation) -> BankSystem::OpResult
{
    std::array<UserID, 2> users;
    if (auto result = CheckPreconditions(operation); result.has_value()) { users = result.value(); }
    else { return std::unexpected(result.error()); }

    auto& balance = m_UsersData[users[0]].balance;
    switch (operation.type)
    {
        case OperationType::CashIn:
            balance.Add(operation.amounts[0]);
            break;
        case OperationType::CashOut:
            balance.Sub(operation.amounts[0]);
            break;
        case OperationType::Transfer: {
            balance.Sub(operation.amounts[0]);
            auto& otherBalance = m_UsersData[users[1]].balance;
            otherBalance.Add(operation.amounts[0]);
        }
        break;
        case OperationType::Suspend:
            m_UsersData[users[0]].status = UserStatus::Suspended;
            return {OperationResult{}};
    }

    return {OperationResult{balance}};
}

auto BankSystem::FindUser(std::string_view name) const -> std::expected<UserID, OperationError>
{

    for (const auto& [id, user]: m_Users)
    {
        if (user.GetName() == name) return id;
    }

    return std::unexpected(OperationError::UserNotFound);
}

auto BankSystem::GetUserBalance(std::string_view name) const -> std::expected<CashT, OperationError>
{
    if (auto result = FindUser(name); result.has_value()) { return m_UsersData.at(result.value()).balance; }
    else { return std::unexpected(result.error()); }
}

auto BankSystem::GetUserStatus(std::string_view name) const -> std::expected<UserStatus, OperationError>
{
    if (auto result = FindUser(name); result.has_value()) { return m_UsersData.at(result.value()).status; }
    else { return std::unexpected(result.error()); }
}

auto BankSystem::CheckPreconditions(OpData& operation) -> std::expected<std::array<UserID, 2>, OperationError>
{
    std::array<UserID, 2> users;
    if (auto result = FindUser(operation.users[0]); result.has_value()) { users[0] = result.value(); }
    else { return std::unexpected(result.error()); }

    switch (operation.type)
    {
        case OperationType::CashOut:
        case OperationType::Transfer:
            if (m_UsersData[users[0]].status == UserStatus::Suspended)
                return std::unexpected(OperationError::UserSuspended);
            if (m_UsersData[users[0]].balance < operation.amounts[0])
                return std::unexpected(OperationError::InsufficientFunds);
            break;
        case OperationType::CashIn:
        case OperationType::Suspend:
            break;
        default:
            return std::unexpected(OperationError::UnknownError);
    }

    switch (operation.type)
    {
        case OperationType::Transfer:
            if (auto result = FindUser(operation.users[1]); result.has_value()) { users[1] = result.value(); }
            else { return std::unexpected(result.error()); }
            break;
        default:
            break;
    }

    return users;
}

auto BankSystem::PrintData() -> void
{
    LOG("===============================");
    for (const auto& [id, user]: m_Users)
    {
        auto& data = m_UsersData[id];
        LOG("User: {} Balance: {:.2f}{}", user.GetName().data(), data.balance.GetAmountAsDouble(),
            Currency::GetName(data.balance.GetType()));
    }
    LOG("===============================");
}