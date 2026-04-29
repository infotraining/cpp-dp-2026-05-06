#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <iostream>
#include <string>

class Colleague;
class ConcreteColleague1;
class ConcreteColleague2;

// "Mediator"
class Mediator
{
public:
    virtual void send(const std::string& message, Colleague* colleague) = 0;
    virtual ~Mediator() {}
};

// "ConcreteMediator"
class ConcreteMediator : public Mediator
{
    ConcreteColleague1* colleague1_;
    ConcreteColleague2* colleague2_;

public:
    void set_colleague1(ConcreteColleague1* coll1)
    {
        colleague1_ = coll1;
    }

    void set_colleague2(ConcreteColleague2* coll2)
    {
        colleague2_ = coll2;
    }

    void send(const std::string& message, Colleague* colleague);
};

// "Colleague"
class Colleague
{
protected:
    Mediator* mediator_;

public:
    Colleague(Mediator* mediator) : mediator_(mediator)
    {
    }
};

// "ConcreteColleague1"
class ConcreteColleague1 : public Colleague
{
public:
    ConcreteColleague1(Mediator* mediator) : Colleague(mediator)
    {
    }

    void send(const std::string& message)
    {
        mediator_->send(message, this);
    }

    void notify(const std::string& message)
    {
        std::cout << "Colleague1 gets message: " << message << std::endl;
    }
};

// "ConcreteColleague2"
class ConcreteColleague2 : public Colleague
{
public:
    ConcreteColleague2(Mediator* mediator) : Colleague(mediator)
    {
    }

    void send(const std::string& message)
    {
        mediator_->send(message, this);
    }

    void notify(const std::string& message)
    {
        std::cout << "Colleague2 gets message: " << message << std::endl;
    }
};

void ConcreteMediator::send(const std::string& message, Colleague* colleague)
{
    if (colleague == colleague1_)
    {
        colleague2_->notify(message);
    }
    else
    {
        colleague1_->notify(message);
    }
}

#endif /*MEDIATOR_HPP_*/
