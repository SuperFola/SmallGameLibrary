#include <Small/Graphics/TileView.hpp>

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable:4244)
#endif

namespace sgl::Graphics
{
    TileView::TileView() :
        m_tileSize(16, 16)
    {}

    TileView::TileView(const sf::Vector2i& center, const sf::Vector2i& size, const sf::Vector2i& tileSize) :
        m_view(
            sf::Vector2f(tileSize.x * center.x, tileSize.y * center.y),
            sf::Vector2f(tileSize.x * size.x, tileSize.x * size.y)
        ),
        m_tileSize(tileSize)
    {}

    void TileView::use(sf::RenderTarget& window)
    {
        window.setView(m_view);
    }

    void TileView::setTileSize(const sf::Vector2i& tileSize)
    {
        m_tileSize = tileSize;
    }

    void TileView::setCenter(unsigned x, unsigned y)
    {
        setCenterPx(m_tileSize.x * x, m_tileSize.y * y);
    }

    void TileView::setCenterPx(float x, float y)
    {
        m_view.setCenter(x, y);
    }

    void TileView::setSize(unsigned width, unsigned height)
    {
        setSizePx(m_tileSize.x * width, m_tileSize.y * height);
    }

    void TileView::setSizePx(float width, float height)
    {
        m_view.setSize(width, height);
    }

    void TileView::setRotation(float angle)
    {
        m_view.setRotation(angle);
    }

    void TileView::move(unsigned dx, unsigned dy)
    {
        movePx(m_tileSize.x * dx, m_tileSize.y * dy);
    }

    void TileView::movePx(float dx, float dy)
    {
        m_view.move(dx, dy);
    }

    void TileView::rotate(float angle)
    {
        m_view.rotate(angle);
    }

    void TileView::zoom(float factor)
    {
        m_view.zoom(factor);
    }

    float TileView::getRotation() const
    {
        return m_view.getRotation();
    }

    sf::Vector2i TileView::getCenter() const
    {
        return sf::Vector2i(m_view.getCenter().x / m_tileSize.x, m_view.getCenter().y / m_tileSize.y);
    }

    const sf::Vector2f& TileView::getCenterPx() const
    {
        return m_view.getCenter();
    }

    sf::Vector2i TileView::getSize() const
    {
        return sf::Vector2i(m_view.getSize().x / m_tileSize.x, m_view.getSize().y / m_tileSize.y);
    }

    const sf::Vector2f& TileView::getSizePx() const
    {
        return m_view.getSize();
    }

    const sf::Vector2i& TileView::getTileSize() const
    {
        return m_tileSize;
    }
}

#ifdef _MSC_VER
    #pragma warning(pop)
#endif