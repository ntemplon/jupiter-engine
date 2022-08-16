#include <StateMachine.hpp>

StateMachine::State::State(StateMachine &owner) : _owner(owner), _eventResponse()
{
}

void StateMachine::State::entry()
{
}

void StateMachine::State::exit()
{
}

void StateMachine::State::update(const sf::Time deltaT)
{
}

void StateMachine::State::handleEvent(const Event &event)
{
    this->_eventResponse.dispatch(event);
}

void StateMachine::State::registerEventResponse(const std::string eventId, const std::function<void(const Event &)> &response)
{
    this->_eventResponse.subscribe(eventId, response);
}

StateMachine::StateTransition::StateTransition(StateMachine &context,
                                               std::shared_ptr<State> &source,
                                               std::shared_ptr<State> &target,
                                               std::function<void()> &effect)
    : _context(context), _source(source), _target(target), _effect(effect)
{
}

std::shared_ptr<StateMachine::State> &StateMachine::StateTransition::getSourceState() const
{
    return this->_source;
}

std::shared_ptr<StateMachine::State> &StateMachine::StateTransition::getTargetState() const
{
    return this->_target;
}

void StateMachine::StateTransition::effect()
{
    this->_effect();
}