#pragma once

#include <Dispatcher.hpp>
#include <Event.hpp>

#include <SFML/System.hpp>

#include <map>
#include <functional>
#include <memory>

class StateMachine
{
public:
    class State;
    class StateTransition;

    class State
    {
    public:
        State(StateMachine &owner);
        virtual ~State() = default;

        virtual void entry();
        virtual void exit();
        virtual void update(const sf::Time deltaT);

        void handleEvent(const Event &event);

    protected:
        void registerEventResponse(const std::string eventId, const std::function<void(const Event &)> &response);
        void registerTransition(const std::string eventId, StateTransition &transition);

    private:
        StateMachine &_owner;
        Dispatcher _eventResponse;
    };

    class StateTransition
    {
    public:
        StateTransition(std::shared_ptr<State> &source, std::shared_ptr<State> &target);
        virtual ~StateTransition() = default;

        std::shared_ptr<State> &getSourceState() const;
        std::shared_ptr<State> &getTargetState() const;
        virtual bool guard(const Event &trigger) = 0;
        virtual void effect() = 0;

    private:
        std::shared_ptr<State> &_source;
        std::shared_ptr<State> &_target;
    };

    StateMachine(Dispatcher &dispatcher);

    void start(std::shared_ptr<State> &initialState);
    void update(const sf::Time deltaT);
    void executeTransition(StateTransition &transition);
    Dispatcher &getDispatcher() const;
    State &getState() const;

private:
    Dispatcher &_dispatcher;
    std::shared_ptr<State> _currentState;

    void setState(std::shared_ptr<State> &state);
};