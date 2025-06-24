#include "User.hpp"

std::unique_ptr<UserFactory> UserFactory::s_Instance;

auto UserFactory::Destroy() -> void { s_Instance.reset(); }

auto UserFactory::GetInstance() -> UserFactory*
{
    if (!s_Instance) s_Instance = std::make_unique<UserFactory>();
    return s_Instance.get();
}

auto UserFactory::CreateUser(std::string_view name) -> User { return User{name, m_CurrentID++}; }

User::User(std::string_view name, UserID id) : m_Name{name}, m_ID{id} {}

auto User::SetID(UserID id) -> void { m_ID = id; }

auto User::GetID() const -> UserID { return m_ID; }

auto User::GetName() const -> std::string_view { return m_Name; }

auto User::SetName(std::string_view name) -> void { m_Name = name; }
