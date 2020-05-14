#include <Small/GameObjects/Triggers/Manager.hpp>

namespace sgl::GameObjects
{
    TriggerManager& TriggerManager::onUpdate(const sf::Time dt)
    {
        for (auto& pair : m_container)
        {
            pair.second.onUpdate(dt);
        }
    }
}