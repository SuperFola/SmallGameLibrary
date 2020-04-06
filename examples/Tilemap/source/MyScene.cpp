#include <MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <iostream>

MyScene::MyScene(int id) :
    sgl::Scene(id)
{
    const int level[] = {
         0,  1,  1,  1,  1,  1,  1,  1,  1,  2,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
         7,  8,  8,  8,  8,  8,  8,  8,  8,  9,
        14, 15, 15, 15, 15, 15, 15, 15, 15, 16
    };

    if (!m_tilemap.load("assets/tile_atlas.png", sf::Vector2u(64, 64), level, 10, 7))
        std::cout << "couldn't load the tile atlas" << std::endl;
}

void MyScene::onRender(sf::RenderTarget& screen)
{
    screen.draw(m_tilemap);
}