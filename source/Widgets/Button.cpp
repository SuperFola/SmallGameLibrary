#include <Small/Widgets/Button.hpp>

namespace sgl::Widgets
{
    Button::Button(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        Base(id, parent, bounds), m_shape(nullptr),
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

    sf::Sprite* Button::sprite()
    {
        return m_sprite;
    }

    sf::RectangleShape* Button::shape()
    {
        return m_shape;
    }

    void Button::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
    {
        switch (getStyle())
        {
        case Style::Text:
            if (m_shape)
                screen.draw(*m_shape, transform);
            screen.draw(m_text, transform);
            break;

        case Style::Sprite:
            if (m_sprite)
                screen.draw(*m_sprite, transform);
            break;

        case Style::Both:
            if (m_sprite)
                screen.draw(*m_sprite, transform);
            screen.draw(m_text, transform);
            break;
        }
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
}