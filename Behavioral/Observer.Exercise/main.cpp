#include "stock.hpp"

using namespace std;

int main()
{
    Stock misys("Misys", 340.0);
    Stock ibm("IBM", 245.0);
    Stock tpsa("TPSA", 95.0);

    // TODO: create investors and register them as observers for stocks

    // Trading session
    misys.set_price(360.0);
    ibm.set_price(210.0);
    tpsa.set_price(45.0);

    // TODO: unregister one observer

    misys.set_price(380.0);
    ibm.set_price(230.0);
    tpsa.set_price(15.0);
}
