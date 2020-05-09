namespace sgl::GameObjects
{
    template <typename T>
    Manager<T>& Manager<T>::get()
    {
        static Manager<T> instance;
        return instance;
    }

    template <typename T>
    Manager<T>& Manager<T>::add(const std::string& name, T&& object)
    {
        m_container[name] = std::move(object);
        return *this;
    }

    template <typename T>
    bool Manager<T>::has(const std::string& name) const
    {
        return m_container.find(name) != m_container.end();
    }

    template <typename T>
    T& Manager<T>::operator[](const std::string& name)
    {
        return m_container[name];
    }
}