#include "decorator.hpp"
#include <memory>

using namespace std;

void client(Component& c)
{
    c.operation();
}

int main()
{
    // Create ConcreteComponent and two Decorators
    shared_ptr<Component> c = make_shared<ConcreteComponent>();
    shared_ptr<Component> d1 = make_shared<ConcreteDecoratorA>(c);
    shared_ptr<Component> d2 = make_shared<ConcreteDecoratorB>(d1);

    client(*d2);

    cout << "\n\n";
}
