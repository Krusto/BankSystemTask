
#pragma once
#include "Currency.hpp"
#include <string>

class CashT
{
public:
    CashT() = default;
    ~CashT() = default;

    CashT(Currency::Type type, std::string amount) : m_Type{type}, m_Amount{amount} {}

public:
    auto GetType() const -> Currency::Type;

    auto GetAmount() const -> std::string;

    auto GetAmountAsDouble() const -> double;

    auto SetType(Currency::Type type) -> void;

    auto SetAmount(std::string amount) -> void;

    auto Add(const CashT& other) -> void;
    auto Sub(const CashT& other) -> void;

    static auto AsStr(double value) -> std::string;

public:
    auto operator<(const CashT& other) const -> bool;
    auto operator>(const CashT& other) const -> bool;
    auto operator==(const CashT& other) const -> bool;

private:
    auto AsDouble() const -> double;

private:
    Currency::Type m_Type{Currency::Type::BGN};
    std::string m_Amount;
};

constexpr CashT operator""_BGN(long double val) { return {Currency::Type::BGN, CashT::AsStr(val)}; }

constexpr CashT operator""_EUR(long double val) { return {Currency::Type::EUR, CashT::AsStr(val)}; }

constexpr CashT operator""_USD(long double val) { return {Currency::Type::USD, CashT::AsStr(val)}; }
