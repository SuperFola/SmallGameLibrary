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
            static_cast<Base*>(m_children[i].get())->onUpdate(dt);
    }

    void Layout::onEvent(const sf::Event& event)
    {
        for (std::size_t i=0, size=m_children.size(); i < size; ++i)
        {
            Base* child = static_cast<Base*>(m_children[i].get());

            if (child->isListeningToEvents())
            {
                child->onEvent(event);
                // remove focus if a children is focused
                if (child->hasFocus())
                    m_focused = false;
            }
        }
    }

    void Layout::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
    {}
}