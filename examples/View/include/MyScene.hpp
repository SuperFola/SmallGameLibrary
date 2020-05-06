#ifndef examples_view_myscene
#define examples_view_myscene

#include <Small/Core/Scene.hpp>
#include <Small/Graphics/Tilemap.hpp>
#include <Small/Graphics/TileView.hpp>

#include <SFML/Graphics.hpp>
#include <array>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    sf::Texture m_tileset;
    sgl::Graphics::Tilemap m_tilemap;
    sgl::Graphics::TileView m_view;

    sf::RectangleShape m_playerShape;
    sf::Vector2i m_zone;
    float m_viewMovedPx;
    bool m_canMove;

    std::array<int, 16 * 8> m_level;

    sf::Vector2i getCurrentZone(int dx=0, int dy=0);
    bool isValidZone(const sf::Vector2i& zone);
};

#endif