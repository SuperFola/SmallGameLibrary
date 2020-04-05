#include <Small/Core/SceneManager.hpp>

#include <algorithm>

namespace sgl
{
    SceneManager::SceneManager() :
        m_current(-1)
    {}

    SceneManager::~SceneManager()
    {
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
            m_scenes[i]->setState(State::Stopped);
    }

    bool SceneManager::remove(int id)
    {
        if (id == m_current)
            m_current = -1;
        
        auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [id](auto& scene) -> bool {
            return scene->getId() == id;
        });

        if (it != m_scenes.end())
        {
            m_scenes[id]->setState(State::Stopped);
            m_scenes.erase(it);
            return true;
        }
        return false;
    }

    SceneManager& SceneManager::setCurrent(int id)
    {
        if (0 <= id && id < static_cast<int>(m_scenes.size()))
        {
            m_scenes[m_current]->setState(State::Stopped);
            m_current = id;
            m_scenes[m_current]->setState(State::Running);
        }
        return *this;
    }

    SceneManager& SceneManager::handleEvent(const sf::Event& event)
    {
        if (m_current != -1)
            m_scenes[m_current]->handleEvent(event);
        
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->handleEvent(event);
        }

        return *this;
    }

    SceneManager& SceneManager::update(const sf::Time dt)
    {
        if (m_current != -1)
            m_scenes[m_current]->update(dt, *this);
        
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->update(dt, *this);
        }

        return *this;
    }

    SceneManager& SceneManager::render(sf::RenderTarget& screen)
    {
        if (m_current != -1)
            m_scenes[m_current]->render(screen);
        
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->render(screen);
        }

        return *this;
    }
}