#pragma once
#include <cstddef>
#include <string>
#include <string_view>

class User
{
    using UserID = size_t;

public:
    User() = default;
    User(std::string_view name, UserID id);
    User(const User&) = default;
    User(User&&) noexcept = default;
    User& operator=(const User&) = default;
    User& operator=(User&&) noexcept = default;
    ~User() = default;

public:
    auto SetID(UserID id) -> void;
    auto GetID() const -> UserID;
    auto GetName() const -> std::string_view;
    auto SetName(std::string_view name) -> void;

public:
    static auto GetNextID() -> UserID;

private:
    std::string m_Name;
    UserID m_ID{};

public:
    static UserID s_CurrentID;
};