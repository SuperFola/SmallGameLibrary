#include <MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <iostream>

MyScene::MyScene(int id) :
    sgl::Scene(id),
    m_tilemap(sf::Vector2u(10, 7), sf::Vector2u(64, 64), &m_tileset)
{
    if (!m_tileset.loadFromFile("assets/tile_atlas.png"))
        std::cout << "couldn't load the tile atlas" << std::endl;

    const int level[] = {
         0,  1,  1,  1,  1,  1,  1,  1,  1,  2,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
        14, 15, 15, 15, 15, 15, 15, 15, 15, 16
    };

    m_tilemap.build(level);
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    screen.draw(m_tilemap, transform);
}