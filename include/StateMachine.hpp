#pragma once

#include <Dispatcher.hpp>
#include <Event.hpp>

#include <SFML/System.hpp>

class StateMachine
{
public:
    class State
    {
    public:
        State();
        virtual ~State();

        virtual void entry();
        virtual void exit();
        virtual void update(const sf::Time deltaT);

        virtual void handleEvent(const Event event);
    };

    class StateTransition : public Event
    {
    public:
        virtual State &sourceState() const;
        virtual State targetState() const;
        virtual void effect();
    };

    StateMachine(Dispatcher &dispatcher);

    void update(sf::Time deltaT);
    const Dispatcher getDispatcher() const;
    const State &getState() const;
    void setState(State state);

private:
    Dispatcher &_dispatcher;
    State _currentState;
};