#include <LambdaStates.hpp>

LambdaTransition::LambdaTransition(std::shared_ptr<StateMachine::State> &source,
                                   std::shared_ptr<StateMachine::State> &target,
                                   std::function<bool(const Event &)> guard,
                                   std::function<void()> effect)
    : StateTransition(source, target), _guard(guard), _effect(effect)
{
}

bool LambdaTransition::guard(const Event &trigger) const
{
    return this->_guard(trigger);
}

void LambdaTransition::effect() const
{
    this->_effect();
}

LambdaState::LambdaState(StateMachine &owner, std::function<void()> entry, std::function<void()> exit, std::function<void(const sf::Time deltaT)> update)
    : StateMachine::State(owner), _entry(entry), _exit(exit), _update(update)
{
}

void LambdaState::entry()
{
    this->_entry();
}

void LambdaState::exit()
{
    this->exit();
}

void LambdaState::update(const sf::Time deltaT)
{
    this->update(deltaT);
}