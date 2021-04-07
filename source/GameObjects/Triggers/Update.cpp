#include <Small/GameObjects/Triggers/Update.hpp>

namespace sgl::GameObjects
{
    UpdateTrigger::UpdateTrigger(const sf::Time delta, Trigger::Callback_t&& action, int repetitions) :
        Trigger(std::move(action), "UpdateTrigger", repetitions), m_updateDelta(delta),
        m_currentTime(delta)
    {}

    UpdateTrigger::~UpdateTrigger()
    {}

    void UpdateTrigger::update(const sf::Time dt)
    {
        m_currentTime -= dt;
        if (m_currentTime.asSeconds() <= 0.f)
        {
            (*this)();  // call action

            // reset current time if it's meant to be repeated again
            if (m_repetitions > 0)
                m_currentTime = m_updateDelta;
        }
    }
}