namespace sgl
{
    inline int SceneManager::current() const
    {
        return m_current;
    }

    inline Scene* SceneManager::operator[](int id)
    {
        for (std::size_t i=0, end=m_scenes.size(); i < end; ++i)
        {
            if (m_scenes[i]->getId() == id)
                return m_scenes[i].get();
        }
        return nullptr;
    }
}