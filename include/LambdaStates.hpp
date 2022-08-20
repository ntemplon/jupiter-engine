#include <StateMachine.hpp>

class LambdaTransition : public StateMachine::StateTransition
{
public:
    LambdaTransition(std::shared_ptr<StateMachine::State> &target, std::function<bool(const Event &)> guard, std::function<void()> effect);

    bool guard(const Event &trigger) const;
    void effect() const;

private:
    std::function<bool(const Event &)> _guard;
    std::function<void()> _effect;
};

class LambdaState : public StateMachine::State
{
public:
    LambdaState(StateMachine &owner, std::function<void()> entry, std::function<void()> exit, std::function<void(const sf::Time deltaT)> update);

    void entry();
    void exit();
    void update(const sf::Time deltaT);

private:
    std::function<void()> _entry;
    std::function<void()> _exit;
    std::function<void(const sf::Time deltaT)> _update;
};