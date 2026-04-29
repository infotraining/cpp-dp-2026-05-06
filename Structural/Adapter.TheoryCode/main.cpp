#include "adapter.hpp"
#include <iostream>

using namespace std;

class Client
{
public:
    void do_operation(Target& t)
    {
        t.request();
    }
};

int main()
{
    Client client;

    cout << "-- do_operation on ClassAdapter" << endl;
    ClassAdapter cadapter;
    client.do_operation(cadapter);

    cout << endl;

    cout << "-- do_operation on ObjectAdapter" << endl;
    Adaptee adaptee;
    ObjectAdapter oadapter(adaptee);
    client.do_operation(oadapter);
}
