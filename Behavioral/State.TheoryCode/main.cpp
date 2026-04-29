#include "state.hpp"

int main()
{
    // Setup context in a state
    Context c{std::unique_ptr<State>{new ConcreteStateA}};

    // Issue requests, which toggles state
    c.request();
    c.request();
    c.request();
    c.request();
}
