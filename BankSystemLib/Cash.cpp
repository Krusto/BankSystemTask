#include "Cash.hpp"
#include <charconv>
#include <sstream>

auto CashT::GetType() const -> Currency::Type { return m_Type; }

auto CashT::GetAmount() const -> std::string { return m_Amount; }

auto CashT::GetAmountAsDouble() const -> double { return AsDouble(); }

auto CashT::SetType(Currency::Type type) -> void { m_Type = type; }

auto CashT::SetAmount(std::string amount) -> void { m_Amount = amount; }

auto CashT::Add(const CashT& other) -> void
{

    double a = AsDouble();
    double b = Currency::AsBGN(other).AsDouble();
    double c = a + b;
    m_Amount = AsStr(c);
}

auto CashT::Sub(const CashT& other) -> void
{
    double a = AsDouble();
    double b = Currency::AsBGN(other).AsDouble();
    double c = a - b;
    m_Amount = AsStr(c);
}

auto CashT::operator<(const CashT& other) const -> bool { return AsDouble() < Currency::AsBGN(other).AsDouble(); }

auto CashT::operator>(const CashT& other) const -> bool { return AsDouble() > Currency::AsBGN(other).AsDouble(); }

auto CashT::operator==(const CashT& other) const -> bool { return AsDouble() == Currency::AsBGN(other).AsDouble(); }

auto CashT::AsStr(long double value) -> std::string
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

auto CashT::AsDouble() const -> double
{
    double value{};
    std::from_chars(m_Amount.data(), m_Amount.data() + m_Amount.size(), value);
    return value;
}
