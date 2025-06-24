#include "BankSystem.hpp"

int main()
{
    BankSystem system;

    system.RegisterUser("Pesho");
    system.RegisterUser("Ivan");

    system.CashIn("Ivan", 100000.00_EUR);
    system.CashIn("Pesho", 10.00_BGN);
    system.CashIn("Pesho", 10.00_EUR);

    system.PrintData();

    system.SuspendUser("Pesho");
    system.CashOut("Pesho", 10.00_BGN);
    system.Transfer("Pesho", "Ivan", 10.00_BGN);
    system.CashIn("Pesho", 10.00_BGN);
    system.Transfer("Ivan", "Pesho", 10.00_BGN);
    system.PrintData();

    return 0;
}
