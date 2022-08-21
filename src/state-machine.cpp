#include <StateMachine.hpp>

StateMachine::StateMachine(Dispatcher &dispatcher) : _dispatcher(dispatcher),
                                                     _forwardEvents([&](const Event &event)
                                                                    { if (_currentState)
                                                                        {
                                                                            _currentState->handleEvent(event);
                                                                        } })
{
    _dispatcher.subscribeGlobal(_forwardEvents);
}

void StateMachine::start(std::shared_ptr<StateMachine::State> &initialState)
{
    this->setState(initialState);
    this->getState().entry();
}

bool StateMachine::isStarted() const
{
    // _currentState starts out null and is initialized at start(), so this is a direct way to check if we've started
    return _currentState != nullptr;
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