#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <string>
#include <memory>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string& description) : price_{price}, description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string& description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Americano : public CoffeeBase
{
public:
    Americano(float price = 6.0, const std::string& description = "Americano")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect americano.\n";
    }
};

class Decafeinated : public CoffeeBase
{
public:
    Decafeinated(float price = 5.0, const std::string& description = "Decafeinated Coffee")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect decafeinated coffee.\n";
    }
};

// TODO: Add condiments that can be added to coffee: WhippedCream: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$
// Hint#1: Add CoffeeDecorator and concrete decorators for condiments 

class CoffeeDecorator : public Coffee
{
    std::unique_ptr<Coffee> coffee_;
public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee)
        : coffee_{std::move(coffee)}
    {
    }

    float get_total_price() const override { return coffee_->get_total_price(); }
    std::string get_description() const override { return coffee_->get_description(); }
    void prepare() override { coffee_->prepare(); }
};

class WhippedCream : public CoffeeDecorator
{
public: 
    using CoffeeDecorator::CoffeeDecorator;

    float get_total_price() const override
    {
        return CoffeeDecorator::get_total_price() + 2.5f;
    }

    std::string get_description() const override
    {
        return CoffeeDecorator::get_description() + ", Whipped Cream";
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding whipped cream.\n";
    }
};

class Whisky : public CoffeeDecorator
{
public: 
    using CoffeeDecorator::CoffeeDecorator;

    float get_total_price() const override
    {
        return CoffeeDecorator::get_total_price() + 6.0f;
    }

    std::string get_description() const override
    {
        return CoffeeDecorator::get_description() + ", Whisky";
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding whisky.\n";
    }
};

class ExtraEspresso : public CoffeeDecorator
{
public: 
    using CoffeeDecorator::CoffeeDecorator;

    float get_total_price() const override
    {
        return CoffeeDecorator::get_total_price() + 4.0f;
    }

    std::string get_description() const override
    {
        return CoffeeDecorator::get_description() + ", Extra Espresso";
    }

    void prepare() override
    {
        CoffeeDecorator::prepare();
        std::cout << "Adding extra espresso.\n";
    }
};

#endif /*COFFEEHELL_HPP_*/
