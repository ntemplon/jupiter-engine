#pragma once

#include <Dispatcher.hpp>
#include <Event.hpp>

#include <SFML/System.hpp>

#include <functional>

class StateMachine
{
public:
    class State
    {
    public:
        State(StateMachine &owner);
        virtual ~State() = default;

        virtual void entry();
        virtual void exit();
        virtual void update(const sf::Time deltaT);

        virtual void handleEvent(const Event &event);

    private:
        StateMachine &_owner;
    };

    class StateTransition
    {
    public:
        StateTransition(StateMachine &context, State &source, State &target, std::function<void()> effect);

        State &getSourceState() const;
        State &getTargetState() const;
        void effect();

    private:
        StateMachine &_context;
        State &_source;
        State &_target;
        std::function<void()> _effect;
    };

    StateMachine(Dispatcher &dispatcher);

    void update(const sf::Time deltaT);
    Dispatcher &getDispatcher() const;
    State &getState() const;

private:
    Dispatcher &_dispatcher;
    State &_currentState;

    void setState(State &state);
};