#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include "prototype.hpp"

using namespace std;

class PrototypeManager
{
    using PrototypeMap = map<string, shared_ptr<Prototype>>;
    PrototypeMap prototypes_;
public:
    PrototypeManager()
    {}

    void insert(const string& id, shared_ptr<Prototype> prototype)
    {
        prototypes_.insert(make_pair(id, prototype));
    }

    shared_ptr<Prototype> find(const string& id)
    {
        auto item = prototypes_.at(id);

        return item;
    }
};

int main()
{
    PrototypeManager manager;

    shared_ptr<Prototype> p1 = make_shared<ConcretePrototype1>("State A");
    shared_ptr<Prototype> p2 = make_shared<ConcretePrototype1>("State B");
    shared_ptr<Prototype> p3 = make_shared<ConcretePrototype2>(1);
    shared_ptr<Prototype> p4 = make_shared<ConcretePrototype2>(2);

    manager.insert("P1", p1);
    manager.insert("P2", p2);
    manager.insert("P3", p3);
    manager.insert("P4", p4);

    shared_ptr<Prototype> found1 = manager.find("P4");

    unique_ptr<Prototype> cloned1 = found1->clone();

    cloned1->run();
}
