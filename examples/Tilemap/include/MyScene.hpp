#ifndef examples_tilemap_myscene
#define examples_tilemap_myscene

#include <Small/Core/Scene.hpp>
#include <Small/Graphics/Tilemap.hpp>
#include <SFML/Graphics.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    sgl::Graphics::Tilemap m_tilemap;
    sf::Texture m_tileset;
};

#endif