namespace sgl
{
    inline int SceneManager::current() const
    {
        return m_current;
    }

    inline Scene* SceneManager::operator(int id)
    {
        return m_scenes[id].get();
    }
}