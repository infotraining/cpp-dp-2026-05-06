#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <iostream>
#include <set>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
class Observer
{
public:
    virtual void update(TSource&, TEventArgs... args) = 0;
    virtual ~Observer() = default;
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
struct Observable
{
    void subscribe(Observer<TSource, TEventArgs...>* observer)
    {        
        observers_.insert(observer);
    }
    void unsubscribe(Observer<TSource, TEventArgs...>* observer) { observers_.erase(observer); }

protected:
    void notify(TSource& source, TEventArgs... args)
    {
        for (auto&& observer : observers_)
            observer->update(static_cast<TSource&>(*this), std::move(args...));
    }

private:
    std::set<Observer<TSource, TEventArgs...>*> observers_;
};

#endif /*OBSERVER_HPP_*/
