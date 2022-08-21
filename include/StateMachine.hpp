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

        void registerEventResponse(const std::string eventId, const std::function<void(const Event &)> &response);
        void registerTransition(const std::string eventId, const StateTransition &transition);
        void registerTransition(const std::string eventId, std::shared_ptr<State> &target);

    private:
        StateMachine &_owner;
        Dispatcher _eventResponse;
    };

    class StateTransition
    {
    public:
        StateTransition(std::shared_ptr<State> &target);
        virtual ~StateTransition() = default;

        std::shared_ptr<State> &getTargetState() const;
        virtual bool guard(const Event &trigger) const;
        virtual void effect() const;

    private:
        std::shared_ptr<State> &_target;
    };

    StateMachine(Dispatcher &dispatcher);

    void start(std::shared_ptr<State> &initialState);
    bool isStarted() const;
    void update(const sf::Time deltaT);
    void executeTransition(const StateTransition &transition);
    Dispatcher &getDispatcher() const;
    State &getState() const;

private:
    Dispatcher &_dispatcher;
    std::shared_ptr<State> _currentState;
    std::function<void(const Event &)> _forwardEvents;

    void setState(std::shared_ptr<State> &state);
};