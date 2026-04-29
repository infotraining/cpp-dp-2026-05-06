#ifndef STATE_HPP_
#define STATE_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

class Context;

// "State"
class State
{
public:
    virtual std::unique_ptr<State> handle() = 0;
    virtual ~State() {}
};

// "ConcreteStateA"
class ConcreteStateA : public State
{
public:
    std::unique_ptr<State> handle();
};

// "ConcreteStateB"
class ConcreteStateB : public State
{
public:
    std::unique_ptr<State> handle();
};

// "Context"
class Context
{
    std::unique_ptr<State> state_;

public:
    Context(std::unique_ptr<State> initial_state) : state_{std::move(initial_state)}
    {
    }

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    void request()
    {
        state_ = state_->handle();
    }
};

std::unique_ptr<State> ConcreteStateA::handle()
{
    std::cout << "Context works in ConcreteStateA" << std::endl;

    return std::make_unique<ConcreteStateB>();
}

std::unique_ptr<State> ConcreteStateB::handle()
{
    std::cout << "Context works in ConcreteStateB" << std::endl;

    return std::make_unique<ConcreteStateA>();
}

#endif /*STATE_HPP_*/
