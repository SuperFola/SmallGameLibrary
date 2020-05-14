#include <Small/GameObjects/Triggers/Manager.hpp>

namespace sgl::GameObjects
{
    TriggerManager& TriggerManager::update(TriggerManager::Visitor_t&& visitor)
    {
        for (auto& pair : m_container)
            visitor(pair.second);
        return *this;
    }
}