#include <StateMachine.hpp>

void StateMachine::update(const sf::Time deltaT)
{
    this->getState().update(deltaT);
}

Dispatcher &StateMachine::getDispatcher() const
{
    return this->_dispatcher;
}