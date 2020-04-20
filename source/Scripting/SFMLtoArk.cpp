#include <Small/Scripting/SFMLtoArk.hpp>

namespace sgl::Scripting
{
    Ark::Value sfEventToArk(const sf::Event& event)
    {
        Ark::Value e(Ark::ValueType::List);

        switch (event.type)
        {
        case sf::Event::TextEntered:
            e.push_back(static_cast<int>(sfEventType::TextEntered));
            // TODO
            // e.push_back(sf::Utf<8>::decode<std::string>(event.text.unicode));
            break;

        case sf::Event::KeyPressed:
            e.push_back(static_cast<int>(sfEventType::KeyPressed));
            e.push_back(event.key.code);
            break;

        case sf::Event::KeyReleased:
            e.push_back(static_cast<int>(sfEventType::KeyReleased));
            e.push_back(event.key.code);
            break;

        case sf::Event::MouseWheelScrolled:
            e.push_back(static_cast<int>(sfEventType::MouseWheelScrolled));
            e.push_back(event.mouseWheelScroll.delta);
            e.push_back(event.mouseWheelScroll.x);
            e.push_back(event.mouseWheelScroll.y);
            break;

        case sf::Event::MouseButtonPressed:
            e.push_back(static_cast<int>(sfEventType::MouseButtonPressed));
            e.push_back(static_cast<int>(event.mouseButton.button));
            e.push_back(event.mouseButton.x);
            e.push_back(event.mouseButton.y);
            break;

        case sf::Event::MouseButtonReleased:
            e.push_back(static_cast<int>(sfEventType::MouseButtonReleased));
            e.push_back(static_cast<int>(event.mouseButton.button));
            e.push_back(event.mouseButton.x);
            e.push_back(event.mouseButton.y);
            break;

        default:
            break;
        }

        return e;
    }

    Ark::Value sfTimeToArk(const sf::Time dt)
    {
        return Ark::Value(dt.asSeconds());
    }
}