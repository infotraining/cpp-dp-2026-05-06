#ifndef ABSTRACT_FACTORY_HPP_
#define ABSTRACT_FACTORY_HPP_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class AbstractProductA;
class AbstractProductB;

class AbstractFactory
{
public:
    virtual std::unique_ptr<AbstractProductA> create_product_A() = 0;
    virtual std::unique_ptr<AbstractProductB> create_product_B() = 0;
    virtual ~AbstractFactory() = default;
};

class AbstractProductA
{
public:
    virtual std::string description() = 0;
    virtual ~AbstractProductA() = default;
};

class AbstractProductB
{
public:
    virtual std::string description() = 0;
    virtual void interact(AbstractProductA& a) = 0;
    virtual ~AbstractProductB() = default;
};

class ProductA1 : public AbstractProductA
{
public:
    std::string description() override
    {
        return std::string("ProductA1");
    }
};

class ProductB1 : public AbstractProductB
{
public:
    std::string description() override
    {
        return std::string("ProductB1");
    }

    void interact(AbstractProductA& a) override
    {
        std::cout << description() << " interacts with "
                  << a.description() << std::endl;
    }
};

class ProductA2 : public AbstractProductA
{
public:
    std::string description() override
    {
        return std::string("ProductA2");
    }
};

class ProductB2 : public AbstractProductB
{
public:
    std::string description() override
    {
        return std::string("ProductB2");
    }

    void interact(AbstractProductA& a) override
    {
        std::cout << description() << " interacts with "
                  << a.description() << std::endl;
    }
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    std::unique_ptr<AbstractProductA> create_product_A() override
    {
        return std::make_unique<ProductA1>();
    }

    std::unique_ptr<AbstractProductB> create_product_B() override
    {
        return std::make_unique<ProductB1>();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    std::unique_ptr<AbstractProductA> create_product_A() override
    {
        return std::make_unique<ProductA2>();
    }

    std::unique_ptr<AbstractProductB> create_product_B() override
    {
        return std::make_unique<ProductB2>();
    }
};

class Client
{
private:
    std::unique_ptr<AbstractProductA> productA_;
    std::unique_ptr<AbstractProductB> productB_;

public:
    Client(AbstractFactory& factory)
        : productA_(factory.create_product_A())
        , productB_(factory.create_product_B())
    {
    }

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    void run()
    {
        productB_->interact(*productA_);
    }
};

#endif /*ABSTRACT_FACTORY_HPP_*/
