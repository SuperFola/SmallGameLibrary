#include <Small/GameObjects/Triggers/Trigger.hpp>

namespace sgl::GameObjects
{
    Trigger::Trigger(int repetions) :
        m_active(true), m_repetions(repetions)
    {}

    Trigger::~Trigger()
    {}

    void Trigger::operator()()
    {
        m_action();
        m_repetions--;
    }

    int Trigger::getRepetitions() const
    {
        return m_repetions;
    }
}