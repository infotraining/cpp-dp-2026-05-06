#ifndef PROTOTYPE_HPP_
#define PROTOTYPE_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Prototype"
class Prototype
{
public:
    virtual void run() = 0;
    virtual std::unique_ptr<Prototype> clone() = 0;
    virtual ~Prototype() = default;
};

// "ConcretePrototype1"
class ConcretePrototype1 : public Prototype
{
    std::string state_;

public:
    ConcretePrototype1(const std::string& state) : state_(state)
    {
    }

    virtual void run() override
    {
        std::cout << "ConcretePrototype1::run(" << state_ << ")" << std::endl;
    }

    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ConcretePrototype1>(*this);
    }
};

// "ConcretePrototype1"
class ConcretePrototype2 : public Prototype
{
    int state_;

public:
    ConcretePrototype2(int state) : state_{ state }
    {
    }

    virtual void run() override
    {
        std::cout << "ConcretePrototype2::run(" << state_ << ")" << std::endl;
    }

    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ConcretePrototype2>(*this);
    }
};

#endif /*PROTOTYPE_HPP_*/
