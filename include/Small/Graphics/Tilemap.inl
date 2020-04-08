namespace sgl::Graphics
{
    inline void Tilemap::update(const sf::Vector2u& tilePos, int new_tile)
    {
        // find its position in the tileset texture
        int tu = new_tile % (m_tileset->getSize().x / m_tileSize.x);
        int tv = new_tile / (m_tileset->getSize().x / m_tileSize.x);

        int i = tilePos.x;
        int j = tilePos.y;

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(i + j * m_mapSize.x) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f( i      * m_tileSize.x,  j      * m_tileSize.y);
        quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x,  j      * m_tileSize.y);
        quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
        quad[3].position = sf::Vector2f( i      * m_tileSize.x, (j + 1) * m_tileSize.y);

        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f( tu      * m_tileSize.x,  tv      * m_tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x,  tv      * m_tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
        quad[3].texCoords = sf::Vector2f( tu      * m_tileSize.x, (tv + 1) * m_tileSize.y);
    }
}