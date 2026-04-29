#ifndef DECORATOR_HPP_
#define DECORATOR_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Component"
class Component
{
public:
    virtual void operation() = 0;
    virtual ~Component() = default;
};

// "ConcreteComponent"
class ConcreteComponent : public Component
{
public:
    void operation() override
    {
        std::cout << "ConcreteComponent.operation()";
    }
};

// "Decorator"
class Decorator : public Component
{
protected:
    std::shared_ptr<Component> component_;

public:
    Decorator(std::shared_ptr<Component> component)
        : component_(component)
    {
    }

    void set_component(std::shared_ptr<Component> component)
    {
        component_ = component;
    }

    void operation() override
    {
        component_->operation();
    }
};

// "ConcreteDecoratorA"
class ConcreteDecoratorA : public Decorator
{
private:
    std::string added_state_;

public:
    ConcreteDecoratorA(std::shared_ptr<Component> component)
        : Decorator(component)
    {
    }

    void operation() override
    {
        Decorator::operation();
        added_state_ = "added state";
        std::cout << " and decorated with " << added_state_;
    }
};

// "ConcreteDecoratorB"
class ConcreteDecoratorB : public Decorator
{
private:
    std::string added_behaviour()
    {
        return std::string("added behaviour");
    }

public:
    ConcreteDecoratorB(std::shared_ptr<Component> component)
        : Decorator(component)
    {
    }

    void operation() override
    {
        Decorator::operation();
        std::cout << " and decorated with " << added_behaviour();
    }
};

#endif /*DECORATOR_HPP_*/
