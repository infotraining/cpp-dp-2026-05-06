#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <string>

// TODO: Define Observer interface
class Observer
{
public:
    virtual void update(/*...*/) = 0;
    virtual ~Observer()
    {
    }
};

// TODO: Implement the class that sends notification on price change
class Stock
{
private:
    std::string symbol_;
    double price_;
    // TODO: add container that holds observers
public:
    Stock(const std::string& symbol, double price) : symbol_(symbol), price_(price)
    {
    }

    std::string get_symbol() const
    {
        return symbol_;
    }

    double get_price() const
    {
        return price_;
    }

    // TODO: subscribe observer

    // TODO: unsubscribe observer

    void set_price(double price)
    {
        price_ = price;

        // TODO: notify observers on changing the stock price
    }
};

class Investor : public Observer
{
    std::string name_;

public:
    Investor(const std::string& name) : name_(name)
    {
    }

    void update(/*...*/)
    {
        // TODO: implement callback
    }
};

#endif /*STOCK_HPP_*/
