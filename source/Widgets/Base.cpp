#include <Small/Widgets/Base.hpp>

namespace sgl::Widgets
{
    Base::Base(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        m_id(id), m_listening(true), m_rect(bounds), m_parent(parent),
        m_style(Style::Text)
    {
        setPosition(bounds.left, bounds.top);
    }

    Base::~Base()
    {}

    void Base::onUpdate(const sf::Time dt)
    {}

    void Base::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
    {}

    void Base::onEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::TextEntered:
            if (m_focused)
                onTextEntered(event.text.unicode);
            break;

        case sf::Event::KeyPressed:
            if (m_focused)
                onKeyPressed(event.key.code);
            break;

        case sf::Event::KeyReleased:
            if (m_focused)
                onKeyReleased(event.key.code);
            break;

        case sf::Event::MouseWheelScrolled:
            if (m_focused)
                onMouseWheelScrolled(event.mouseWheelScroll.delta);
            break;

        case sf::Event::MouseButtonPressed:
            if (getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                m_focused = true;
            else
                m_focused = false;

            if (m_focused)
                onMouseButtonPressed(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            break;

        case sf::Event::MouseButtonReleased:
            if (getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
                m_focused = true;
            else
                m_focused = false;

            if (m_focused)
                onMouseButtonReleased(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            break;

        default:
            break;
        }
    }

    void Base::onTextEntered(sf::Uint32 code)
    {}

    void Base::onKeyPressed(int key)
    {}

    void Base::onKeyReleased(int key)
    {}

    void Base::onMouseWheelScrolled(float delta)
    {}

    void Base::onMouseButtonPressed(int button, int x, int y)
    {}

    void Base::onMouseButtonReleased(int button, int x, int y)
    {}

    sf::FloatRect Base::getLocalBounds() const
    {
        float width = static_cast<float>(std::abs(m_rect.width));
        float height = static_cast<float>(std::abs(m_rect.height));
        return sf::FloatRect(0.f, 0.f, width, height);
    }

    sf::FloatRect Base::getGlobalBounds() const
    {
        sf::FloatRect bounds = getTransform().transformRect(getLocalBounds());
        if (m_parent)
        {
            bounds.left += m_parent->getGlobalBounds().left;
            bounds.top  += m_parent->getGlobalBounds().top;
        }
        return bounds;
    }

    void Base::setListenToEvents(bool value)
    {
        m_listening = value;
    }

    bool Base::isListeningToEvents() const
    {
        return m_listening;
    }

    bool Base::hasFocus() const
    {
        return m_focused;
    }

    void Base::setStyle(Style style)
    {
        m_style = style;
    }

    Style Base::getStyle() const
    {
        return m_style;
    }

    void Base::setPosition(int x, int y)
    {
        float fx = static_cast<float>(x);
        float fy = static_cast<float>(y);

        sf::Transformable::setPosition(fx, fy);
    }

    void Base::draw_(sf::RenderTarget& target, const sf::Transform& parentTransform)
    {
        sf::Transform combinedTransform = parentTransform * getTransform();
        onRender(target, combinedTransform);
    }
}