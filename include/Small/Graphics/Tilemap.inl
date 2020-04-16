#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable:4244)
#endif

namespace sgl::Graphics
{
    inline void Tilemap::update(const sf::Vector2i& tilePos, int new_tile)
    {
        // find its position in the tileset texture
        int tu = new_tile % (m_tileset->getSize().x / m_tileSize);
        int tv = new_tile / (m_tileset->getSize().x / m_tileSize);

        int i = tilePos.x;
        int j = tilePos.y;

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(i + j * m_mapSize.x) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f( i      * m_tileSize,  j      * m_tileSize);
        quad[1].position = sf::Vector2f((i + 1) * m_tileSize,  j      * m_tileSize);
        quad[2].position = sf::Vector2f((i + 1) * m_tileSize, (j + 1) * m_tileSize);
        quad[3].position = sf::Vector2f( i      * m_tileSize, (j + 1) * m_tileSize);

        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f( tu      * m_tileSize,  tv      * m_tileSize);
        quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize,  tv      * m_tileSize);
        quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize, (tv + 1) * m_tileSize);
        quad[3].texCoords = sf::Vector2f( tu      * m_tileSize, (tv + 1) * m_tileSize);
    }
}

#ifdef _MSC_VER
    #pragma warning(pop)
#endif