#include <Small/Core/Scene.hpp>

namespace sgl
{
    Scene::Scene(int id) :
        m_id(id), m_state(State::Stopped)
    {}

    void Scene::setState(State state)
    {
        m_state = state;
    }
}