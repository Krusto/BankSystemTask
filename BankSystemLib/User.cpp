#include "User.hpp"

User::UserID User::s_CurrentID = 0;

User::User(std::string_view name, UserID id) : m_Name{name}, m_ID{id} {}

auto User::SetID(UserID id) -> void { m_ID = id; }

auto User::GetID() const -> UserID { return m_ID; }

auto User::GetName() const -> std::string_view { return m_Name; }

auto User::SetName(std::string_view name) -> void { m_Name = name; }

auto User::GetNextID() -> UserID { return s_CurrentID++; }
