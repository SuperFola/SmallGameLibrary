#include <Small/Core/SceneManager.hpp>

#include <Small/Scripting/Bindings.hpp>
#include <algorithm>

namespace sgl
{
    SceneManager::SceneManager() :
        m_current(-1)
    {}

    SceneManager::~SceneManager()
    {
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i])
                m_scenes[i]->setState(State::Stopped);
        }
    }

    bool SceneManager::remove(int id)
    {
        if (id == m_current)
            m_current = -1;

        for (std::size_t i = 0, end = m_scenes.size(); i < end; ++i)
        {
            if (m_scenes[i] && m_scenes[i]->getId() == id)
            {
                // replace object, causing it to be destroyed and freed
                m_scenes[i] = nullptr;
                return true;
            }
        }

        return false;
    }

    SceneManager& SceneManager::setCurrentId(int id, void* data)
    {
        for (std::size_t i = 0, end = m_scenes.size(); i < end; ++i)
        {
            if (m_scenes[i] && m_scenes[i]->getId() == id)
            {
                if (m_current != -1)
                    m_scenes[m_current]->setState(State::Stopped);
                m_current = id;
                m_scenes[m_current]->setState(State::Running);

                // call the onChange method of the scene to notify it
                // that the current running scene has changed
                m_scenes[m_current]->onChange(data);
                break;
            }
        }

        return *this;
    }

    SceneManager& SceneManager::init(const Scripting::Config& config)
    {
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i])
                m_scenes[i]->init(config);
        }
        return *this;
    }

    SceneManager& SceneManager::onEvent(const sf::Event& event)
    {
        if (m_current != -1)
            m_scenes[m_current]->onEvent(event);

        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i] && m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->onEvent(event);
        }

        return *this;
    }

    SceneManager& SceneManager::onUpdate(const sf::Time dt)
    {
        if (m_current != -1)
            m_scenes[m_current]->onUpdate(dt);

        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i] && m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->onUpdate(dt);
        }

        return *this;
    }

    SceneManager& SceneManager::onRender(sf::RenderTarget& screen)
    {
        if (m_current != -1)
            m_scenes[m_current]->render(screen, m_transform);  // the method onRender is automatically called by render()

        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i] && m_scenes[i]->getState() == State::Idle)
                m_scenes[i]->render(screen, m_transform);
        }

        return *this;
    }

    SceneManager& SceneManager::onQuit()
    {
        for (std::size_t i = 0, size = m_scenes.size(); i < size; ++i)
        {
            if (m_scenes[i])
                m_scenes[i]->onQuit();
        }

        return *this;
    }
}