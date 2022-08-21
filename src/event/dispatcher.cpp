#include <Dispatcher.hpp>

#include <iostream>

void Dispatcher::subscribe(const std::string type, const std::function<void(const Event &)> observer)
{
    // Push to back so the call order matches subscriber order
    _observers[type].push_back(observer);
}

void Dispatcher::subscribeGlobal(const std::function<void(const Event &)> observer)
{
    // Push to back so the call order matches subscriber order
    _globalObservers.push_back(observer);
}

void Dispatcher::dispatch(const Event &event)
{
    if (_observers.find(event.getType()) != _observers.end())
    {
        // Case - one or more observers has subscribed to this event
        // Iterate through all of them and invoke each one in order
        for (std::function<void(const Event &)> &observer : _observers.at(event.getType()))
        {
            observer(event);
        }
    }

    // Send the event to the global listeners, in subscription order
    for (auto &observer : _globalObservers)
    {
        observer(event);
    }
}