#include "BankSystem.hpp"

void Check(BankSystem::OpResult&& result) {}

int main()
{
    BankSystem system;


    system.RegisterUser("Pesho");
    system.RegisterUser("Ivan");

    Check(system.CashIn("Ivan", 100000.00_EUR));
    Check(system.CashIn("Pesho", 10.00_BGN));
    Check(system.CashIn("Pesho", 10.00_EUR));

    system.PrintData();

    Check(system.SuspendUser("Pesho"));
    Check(system.CashOut("Pesho", 10.00_BGN));
    Check(system.Transfer("Pesho", "Ivan", 10.00_BGN));
    Check(system.CashIn("Pesho", 10.00_BGN));
    Check(system.Transfer("Ivan", "Pesho", 10.00_BGN));
    system.PrintData();

    return 0;
}
