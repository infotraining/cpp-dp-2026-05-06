#include <iostream>

#include "bank_account.hpp"

using namespace std;

int main()
{
    using namespace Bank;

    BankAccount ba{ 1 };

    ba.deposit(100);
    cout << ba.status() << endl;

    ba.deposit(200);
    cout << ba.status() << endl;

    ba.withdraw(150);
    cout << ba.status() << endl;

    ba.withdraw(400);
    cout << ba.status() << endl;

    try
    {
        ba.withdraw(200);
    }
    catch (const InsufficientFunds& e)
    {
        cout << e.what() << endl;
    }

    ba.deposit(100);
    cout << ba.status() << endl;

    ba.deposit(500);
    cout << ba.status() << endl;
}
