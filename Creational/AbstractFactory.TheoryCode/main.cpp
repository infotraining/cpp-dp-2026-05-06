#include "abstract_factory.hpp"
#include <iostream>

using namespace std;

int main()
{    
    ConcreteFactory1 factory1;
    Client client1(factory1);
    client1.run();

    ConcreteFactory2 factory2;
    Client client2(factory2);
    client2.run();
}
