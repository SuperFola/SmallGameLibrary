#include <Small/Core/Scene.hpp>

#include <Small/Core/SceneManager.hpp>

namespace sgl
{
    Scene::Scene(int id) :
        m_id(id), m_state(State::Stopped)
    {}

    Scene::~Scene()
    {}

    void Scene::onEvent(const sf::Event& event)
    {}

    void Scene::onUpdate(const sf::Time dt, SceneManager& scm)
    {}

    void Scene::onRender(sf::RenderTarget& screen)
    {}

    void Scene::onQuit()
    {}

    void Scene::setState(State state)
    {
        m_state = state;
    }
}