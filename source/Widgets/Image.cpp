#include <Small/Widgets/Image.hpp>

namespace sgl::Widgets
{
    Image::Image(int id, Base::Ptr parent, const sf::IntRect& bound) :
        Base(id, parent, bound)
    {}

    Image::~Image()
    {}

    sf::Sprite& Image::sprite()
    {
        return m_sprite;
    }

    void Image::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
    {
        screen.draw(m_sprite, transform);
    }
}