#include <MyScene.hpp>

#include <iostream>
#include <cmath>

// TODO remove magic constants

MyScene::MyScene(int id) :
    sgl::Scene(id),
    //        map size (tiles)     tile size (px)
    m_tilemap(sf::Vector2i(16, 16), 16),
    m_playerShape(sf::Vector2f(16, 16)), m_viewMovedPx(0),
    m_canMove(true)
{
    m_tileset.loadFromFile("assets/tileset.png");
    m_tilemap.use(&m_tileset);

    // build level
    m_level = {
         47,  46,  47,  35,  36,  36,  36,  37,  46,  45,  61,  47,  38,  42, 248,  39,
         63,  62,  63, 116, 116, 116, 116,  46,  45,  61,  45,  63,  38, 248,  43,  39,
         58,  58, 116,  16,  17,  17,  18,  62,  61,  45,  61,  47,  38, 248,  43,  39,
         33,  34, 116,  22, 241,  27,  23,  46,  45,  61,  45,  63,  38,  43,  43,  37,
         43,  43, 242,  19,  27,  27,  21,  62,  63,  62,  63,  32,  43,  42,  39,  46,
         42,  43,  34, 116,  19,  21, 116,  32,  33,  33,  33,  43, 248, 248,  39,  62,
         36,  43,  39,  58, 192, 192,  58,  35,  36,  36,  36,  36,  36,  43, 248,  34,
         58,  35,  37,  58,  58,  58,  58, 243,  58,  58,  58,  58,  58,  35,  36,  37
    };

    m_tilemap.build(m_level.data());

    // center view on the left most 8x8 part of the map
    m_view.setCenter(4, 4);  // top left corner of the tile at (x=4, y=4)
    m_view.setSize(8, 8);

    m_zone = getCurrentZone();
}

void MyScene::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && m_canMove)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Z:
            if (isValidZone(getCurrentZone(0, -16)))
                m_playerShape.move(0, -16);
            break;
        
        case sf::Keyboard::Q:
            if (isValidZone(getCurrentZone(-16, 0)))
                m_playerShape.move(-16, 0);
            break;
        
        case sf::Keyboard::S:
            if (isValidZone(getCurrentZone(0, 16)))
                m_playerShape.move(0, 16);
            break;
        
        case sf::Keyboard::D:
            if (isValidZone(getCurrentZone(16, 0)))
                m_playerShape.move(16, 0);
            break;
        }
    }
}

void MyScene::onUpdate(const sf::Time dt)
{
    // move view
    sf::Vector2i newZone = getCurrentZone();
    if (m_zone != newZone)
    {
        // direction
        sf::Vector2i diff = newZone - m_zone;
        // block player movements
        m_canMove = false;
        // scrolling speed
        const int tiles_per_second = 16 * 5;
        // movement to do
        float dx = tiles_per_second * dt.asSeconds() * diff.x;
        float dy = tiles_per_second * dt.asSeconds() * diff.y;
        // move
        m_view.movePx(dx, dy);
        // update moved quantity
        m_viewMovedPx += std::abs(dx) + std::abs(dy);

        std::cout << m_viewMovedPx << "\n";

        if (m_viewMovedPx >= 16 * 8)
        {
            m_zone = newZone;
            m_view.setCenter(newZone.x * 8 + 4, newZone.y * 8 + 4);
            m_viewMovedPx = 0;
        }
    }
    else
    {
        m_canMove = true;
    }
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    m_view.use(screen);
    screen.draw(m_tilemap, transform);
    screen.draw(m_playerShape, transform);
}

sf::Vector2i MyScene::getCurrentZone(int dx, int dy)
{
    //  16 = size of a tile in pixels       8 = width of a zone            8 = height of a zone
    return sf::Vector2i(
        static_cast<int>(m_playerShape.getPosition().x + dx) / (8 * 16),
        static_cast<int>(m_playerShape.getPosition().y + dy) / (8 * 16)
    );
}

bool MyScene::isValidZone(const sf::Vector2i& zone)
{
    if (zone.y != 0)
        return false;
    if (zone.x < 0 || zone.x > 1)
        return false;
    return true;
}