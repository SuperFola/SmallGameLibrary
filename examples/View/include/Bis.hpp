#ifndef examples_view_bis
#define examples_view_bis

#include <Small/Scenes/Zone.hpp>
#include <Small/Graphics/Tilemap.hpp>
#include <Small/Graphics/TileView.hpp>

#include <SFML/Graphics.hpp>
#include <array>

class Bis : public sgl::Scenes::Zone
{
public:
    Bis(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    sf::Texture m_tileset;
    sgl::Graphics::Tilemap m_tilemap;

    sf::RectangleShape m_playerShape;
    bool m_canMove;

    std::array<int, 16 * 8> m_level;
};

#endif