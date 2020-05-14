#include <Small/GameObjects/Triggers/Update.hpp>

namespace sgl::GameObjects
{
    UpdateTrigger::UpdateTrigger(const sf::Time delta, Trigger::Callback_t&& action, int repetitions) :
        Trigger(action, "UpdateTrigger", repetitions), m_updateDelta(delta),
        m_currentTime(delta)
    {}

    UpdateTrigger::~UpdateTrigger()
    {}

    void UpdateTrigger::update(const sf::Time dt)
    {
        m_currentTime -= dt;
        if (m_currentTime.asSeconds() <= 0.f)
            (*this)();  // call action

        m_currentTime += delta;
    }
}