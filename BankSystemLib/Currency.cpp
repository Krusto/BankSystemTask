#include "Currency.hpp"
#include "Cash.hpp"

std::array<const char*, std::to_underlying(Currency::Type::NUM_CURRENCIES)> Currency::s_Names;
std::array<double, std::to_underlying(Currency::Type::NUM_CURRENCIES)> Currency::s_ConversionRates;

auto Currency::RegisterCurrencies() -> void
{
    Currency::s_Names = {"BGN", "EUR", "USD"};
    Currency::s_ConversionRates = {1.0, 1.95, 1.80};
}

auto Currency::AsBGN(const CashT& cash) -> CashT
{
    auto conversionRate = GetConversionRate(cash.GetType());
    double convertedAmount = cash.GetAmountAsDouble() * conversionRate;

    return {Currency::Type::BGN, CashT::AsStr(convertedAmount)};
}

auto Currency::GetName(Currency::Type type) -> const char* { return Currency::s_Names.at(std::to_underlying(type)); }

auto Currency::GetConversionRate(Currency::Type type) -> double
{
    return Currency::s_ConversionRates.at(std::to_underlying(type));
}