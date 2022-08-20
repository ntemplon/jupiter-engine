#include <StateMachine.hpp>

StateMachine::StateMachine(Dispatcher &dispatcher) : _dispatcher(dispatcher)
{
}

void StateMachine::update(const sf::Time deltaT)
{
    this->getState().update(deltaT);
}

Dispatcher &StateMachine::getDispatcher() const
{
    return this->_dispatcher;
}

StateMachine::State &StateMachine::getState() const
{
    return *(this->_currentState);
}

void StateMachine::setState(std::shared_ptr<State> &state)
{
    this->_currentState = state;
}

void StateMachine::executeTransition(const StateTransition &transition)
{
    this->getState().exit();
    this->setState(transition.getTargetState());
    transition.effect();
    this->getState().entry();
}