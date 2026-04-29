#include "mediator.hpp"

using namespace std;

int main()
{
    ConcreteMediator m;

    ConcreteColleague1 c1{&m};
    ConcreteColleague2 c2{&m};

    m.set_colleague1(&c1);
    m.set_colleague2(&c2);

    c1.send("How are you?");
    c2.send("Fine, thanks");
}
