namespace sgl
{
    inline const int Scene::getId() const final
    {
        return m_id;
    }

    inline const State Scene::getState() const final
    {
        return m_state;
    }
}