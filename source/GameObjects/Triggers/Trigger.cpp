#include <Small/GameObjects/Triggers/Trigger.hpp>

namespace sgl::GameObjects
{
    Trigger::Trigger(Trigger::Callback_t&& action, const std::string& triggerType, int repetitions) :
        m_active(true), m_repetitions(repetitions), m_action(std::move(action)),
        m_triggerType(triggerType)
    {}

    Trigger::~Trigger()
    {}

    void Trigger::operator()()
    {
        m_action();
        m_repetitions--;
    }

    int Trigger::getRepetitions() const
    {
        return m_repetitions;
    }

    const std::string& Trigger::getTriggerType() const
    {
        return m_triggerType;
    }
}