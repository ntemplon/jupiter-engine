#include <StateMachine.hpp>

// ==========================================================================================================================================
//                                  StateMachine::State
// ==========================================================================================================================================
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

void StateMachine::State::registerTransition(const std::string eventId, StateMachine::StateTransition &transition)
{
    // Assert that the transition starts here?
    this->registerEventResponse(eventId, [&](const Event &event)
                                { if(transition.guard(event)) _owner.executeTransition(transition); });
}

// ==========================================================================================================================================
//                                  StateMachine::StateTransition
// ==========================================================================================================================================
StateMachine::StateTransition::StateTransition(std::shared_ptr<State> &source,
                                               std::shared_ptr<State> &target,
                                               std::function<bool(const Event &)> guard,
                                               std::function<void()> effect)
    : _source(source), _target(target), _guard(guard), _effect(effect)
{
}

StateMachine::StateTransition::StateTransition(std::shared_ptr<State> &source,
                                               std::shared_ptr<State> &target) : StateMachine::StateTransition(
                                                                                     source,
                                                                                     target,
                                                                                     [](const Event &event)
                                                                                     { return true; },
                                                                                     []()
                                                                                     { return; })
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

bool StateMachine::StateTransition::guard(const Event &trigger)
{
    return this->_guard(trigger);
}

void StateMachine::StateTransition::effect()
{
    this->_effect();
}