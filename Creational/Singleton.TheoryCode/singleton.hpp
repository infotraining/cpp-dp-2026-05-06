#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <iostream>

class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& instance()
    {
        if (!instance_)
        {
            instance_ = new Singleton();
        }

        return *instance_;
    }

    void do_something();

private:
    static Singleton* instance_; // uniqueInstance

    Singleton() // disallows creation of new instances outside the class
    {
        std::cout << "Constructor of singleton" << std::endl;
    }

    ~Singleton()
    {
        std::cout << "Singleton has been destroyed!" << std::endl;
    }
};

Singleton* Singleton::instance_ = nullptr;

void Singleton::do_something()
{
    std::cout << "Singleton instance at " << std::hex << &instance() << std::endl;
}

#endif /*SINGLETON_HPP_*/
