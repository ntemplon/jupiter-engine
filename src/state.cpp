#include <StateMachine.hpp>

StateMachine::State::State(StateMachine &owner) : _owner(owner)
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
}

StateMachine::StateTransition::StateTransition(StateMachine &context,
                                               State &source,
                                               State &target,
                                               std::function<void()> effect)
    : _context(context), _source(source), _target(target), _effect(effect)
{
}

StateMachine::State &StateMachine::StateTransition::getSourceState() const
{
    return this->_source;
}

StateMachine::State &StateMachine::StateTransition::getTargetState() const
{
    return this->_target;
}

void StateMachine::StateTransition::effect()
{
    this->_effect();
}