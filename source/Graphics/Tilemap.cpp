#include <Small/Graphics/Tilemap.hpp>

namespace sgl::Graphics
{
    Tilemap::Tilemap(const sf::Vector2u& mapSize, const sf::Vector2u& tileSize, sf::Texture* texture) :
        m_mapSize(mapSize), m_tileSize(tileSize), m_tileset(texture)
    {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(m_mapSize.x * m_mapSize.y * 4);
    }

    void Tilemap::build(const int* tiles)
    {
        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < m_mapSize.x; ++i)
        {
            for (unsigned int j = 0; j < m_mapSize.y; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * m_mapSize.x];
                update(sf::Vector2u(i, j), tileNumber);
            }
        }
    }

    void Tilemap::use(sf::Texture* newTexture)
    {
        m_tileset = newTexture;
    }

    void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
}