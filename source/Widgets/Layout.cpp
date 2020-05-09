#include <Small/Widgets/Layout.hpp>

#include <SFML/Graphics.hpp>

namespace sgl::Widgets
{
    Layout::Layout(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        Base(id, parent, bounds)
    {}

    Layout::~Layout()
    {}

    void Layout::onUpdate(const sf::Time dt)
    {
        for (std::size_t i=0, size=m_children.size(); i < size; ++i)
        {
            m_children[i]->onUpdate(dt);
        }
    }

    void Layout::onEvent(const sf::Event& event)
    {
        for (std::size_t i=0, size=m_children.size(); i < size; ++i)
        {
            if (m_children[i]->isListeningToEvents())
            {
                m_children[i]->onEvent(event);

                // remove focus if a children is focused
                if (m_children[i]->hasFocus())
                    m_focused = false;
            }
        }
    }

    Base* Layout::operator[](int i) const
    {
        return m_children[i].get();
    }

    void Layout::draw_(sf::RenderTarget& target, const sf::Transform& parentTransform)
    {
        sf::Transform combinedTransform = parentTransform * getTransform();

        onRender(target, combinedTransform);
        for (std::size_t i=0, size=m_children.size(); i < size; ++i)
            m_children[i]->draw_(target, combinedTransform);
    }

    void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        const_cast<Layout*>(this)->draw_(target, states.transform);
    }
}