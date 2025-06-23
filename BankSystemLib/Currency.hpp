
#pragma once
#include <array>
#include <cstddef>
#include <utility>

class CashT;

class Currency
{
public:
    Currency() = delete;
    ~Currency() = delete;

public:
    enum class Type : size_t
    {
        BGN,
        EUR,
        USD,
        NUM_CURRENCIES
    };

public:
    static auto RegisterCurrencies() -> void;
    static auto AsBGN(const CashT& cash) -> CashT;
    static auto GetName(Currency::Type type) -> const char*;
    static auto GetConversionRate(Currency::Type type) -> double;

public:
    static std::array<const char*, std::to_underlying(Type::NUM_CURRENCIES)> s_Names;
    static std::array<double, std::to_underlying(Type::NUM_CURRENCIES)> s_ConversionRates;
};