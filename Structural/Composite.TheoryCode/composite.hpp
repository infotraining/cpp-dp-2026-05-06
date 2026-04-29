#ifndef COMPOSITE_HPP_
#define COMPOSITE_HPP_

#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>

// "Component"
class Component
{
protected:
    std::string name_;

public:
    explicit Component(const std::string& name) : name_(name)
    {
    }
	Component(const Component&) = default;
	Component& operator=(const Component&) = default;
    virtual ~Component() = default;
    
    virtual void display(int depth) = 0;
};

using ComponentPtr = std::shared_ptr<Component>;

// "Composite"
class Composite : public Component
{
private:
    std::list<ComponentPtr> children;

public:
    explicit Composite(const std::string& name) : Component(name)
    {
    }

    void add(ComponentPtr c)
    {
        children.push_back(c);
    }

    void remove(ComponentPtr c)
    {
        children.remove(c);
    }

    void display(int depth) override
    {
        std::cout << std::string(depth, '-') << name_ << std::endl;

        for (const auto& child : children)
            child->display(depth + 2);
    }
};

// "Leaf"
class Leaf : public Component
{
public:
    explicit Leaf(const std::string& name) : Component(name)
    {
    }

    void display(int depth) override
    {
        std::cout << std::string(depth, '-') << name_ << std::endl;
    }
};

#endif /*COMPOSITE_HPP_*/
