#include <Bis.hpp>

#include <iostream>
#include <cmath>

Bis::Bis(int id) :
    // tile size = 16, zone size = (8, 8), map size = (2, 1)
    sgl::Scenes::Zone(id, 16, sf::Vector2i(8, 8), sf::Vector2i(2, 1)),
    //   total map size (tiles)     tile size (px)
    m_tilemap(sf::Vector2i(16, 16), 16),
    m_playerShape(sf::Vector2f(16, 16)),
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
}

void Bis::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && m_canMove)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Z:
            if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 0, -16)))
                m_playerShape.move(0, -16);
            break;

        case sf::Keyboard::Q:
            if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), -16, 0)))
                m_playerShape.move(-16, 0);
            break;

        case sf::Keyboard::S:
            if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 0, 16)))
                m_playerShape.move(0, 16);
            break;

        case sf::Keyboard::D:
            if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 16, 0)))
                m_playerShape.move(16, 0);
            break;
        }
    }
}

void Bis::onUpdate(const sf::Time dt)
{
    m_canMove = !makeZoneTransition(m_playerShape.getPosition(), dt, 5 * m_tileSize);
}

void Bis::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    m_view.use(screen);
    screen.draw(m_tilemap, transform);
    screen.draw(m_playerShape, transform);
}