#include "chain.hpp"
#include <array>
#include <iostream>

using namespace std;

int main()
{
    // Setup Chain of Responsibility
    shared_ptr<Handler> h1 = make_shared<ConcreteHandler1>();
    shared_ptr<Handler> h2 = make_shared<ConcreteHandler2>();
    shared_ptr<Handler> h3 = make_shared<ConcreteHandler3>();
    h1->set_successor(h2);
    h2->set_successor(h3);

    // Generate and process request
    array<int, 8> requests = {2, 5, 14, 22, 18, 3, 27, 20};

    for (const auto& r : requests)
    {
        h1->handle_request(r);
    }
}
