#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Handler"
class Handler
{
protected:
    std::shared_ptr<Handler> successor_;

public:
    Handler() : successor_{nullptr} {}

    void set_successor(std::shared_ptr<Handler> successor)
    {
        successor_ = successor;
    }

    virtual void handle_request(int request) = 0;

    virtual ~Handler() = default;
};

// "ConcreteHandler1"
class ConcreteHandler1 : public Handler
{
public:
    void handle_request(int request)
    {
        if ((request >= 0) && (request < 10))
            std::cout << "ConcreteHandler1 handled request " << request << std::endl;
        else if (successor_ != nullptr)
            successor_->handle_request(request);
    }
};

// "ConcreteHandler2"
class ConcreteHandler2 : public Handler
{
public:
    void handle_request(int request)
    {
        if ((request >= 10) && (request < 20))
            std::cout << "ConcreteHandler2 handled request " << request << std::endl;
        else if (successor_ != nullptr)
            successor_->handle_request(request);
    }
};

// "ConcreteHandler3"
class ConcreteHandler3 : public Handler
{
public:
    void handle_request(int request)
    {
        if ((request >= 20) && (request < 30))
            std::cout << "ConcreteHandler3 handled request " << request << std::endl;
        else if (successor_ != nullptr)
            successor_->handle_request(request);
    }
};

#endif /*CHAIN_HPP_*/
