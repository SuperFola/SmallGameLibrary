#include <Small/Widgets/Base.hpp>

namespace sgl::Widgets
{
    Base::Base(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        m_id(id), m_listening(true), m_rect(bounds), m_parent(parent)
    {}

    Base::~Base()
    {}

    void Base::onUpdate(const sf::Time dt)
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
            if (getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                m_focused = true;
            else
                m_focused = false;

            if (m_focused)
                onMouseButtonPressed(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            break;

        case sf::Event::MouseButtonReleased:
            if (getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
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

    sf::FloatRect Base::getLocalBounds() const final
    {
        float width = static_cast<float>(std::abs(m_rect.width));
        float height = static_cast<float>(std::abs(m_rect.height));
        return sf::FloatRect(0.f, 0.f, width, height);
    }

    sf::FloatRect Base::getGlobalBounds() const final
    {
        return getTransform().transformRect(getLocalBounds());
    }

    void Base::setListenToEvents(bool value) final
    {
        m_listening = value;
    }

    bool Base::isListeningToEvents() const final
    {
        return m_listening;
    }

    bool Base::hasFocus() const final
    {
        return m_focused;
    }
}