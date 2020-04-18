#include <Small/Widgets/Label.hpp>

namespace sgl::Widgets
{
    Label::Label(int id, Base::Ptr parent, const sf::IntRect& bounds) :
        Base(id, parent, bounds)
    {
        // we don't need the label to listen to events
        setListenToEvents(false);
    }

    Label::~Label()
    {}

    sf::Text& Label::text()
    {
        return m_text;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_text, states);
    }
}