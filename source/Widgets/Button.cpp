#include <Small/Widgets/Button.hpp>

namespace sgl::Widgets
{
    Button::Button(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        Base(id, parent, bounds), m_shape(sf::Vector2f(bounds.width, bounds.height)),
        m_click(false), m_callback(nullptr)
    {}

    Button::~Button()
    {}

    void Button::setCallback(Callback_t&& callback)
    {
        m_callback = std::move(callback);
    }

    sf::Text& Button::text()
    {
        return m_text;
    }

    sf::Sprite& Button::sprite()
    {
        return m_sprite;
    }

    sf::RectangleShape& Button::shape()
    {
        return m_shape;
    }

    void Button::onMouseButtonPressed(int button, int x, int y)
    {
        m_click = true;
    }

    void Button::onMouseButtonReleased(int button, int x, int y)
    {
        if (m_click && m_callback)
            m_callback();

        m_click = false;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        switch (getStyle())
        {
        case Style::Text:
            target.draw(m_shape, states);
            target.draw(m_text, states);
            break;

        case Style::Sprite:
            target.draw(m_sprite, states);
            break;

        case Style::Both:
            target.draw(m_sprite, states);
            target.draw(m_text, states);
            break;
        }
    }
}