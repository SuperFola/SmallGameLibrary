/**
 * @file Tilemap.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A tilemap wrapper, to render a lot of sprites in a single draw call
 * @version 0.2
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_graphics_tilemap
#define sgl_graphics_tilemap

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sgl::Graphics
{
    /**
     * @brief A tilemap wrapper
     * 
     */
    class Tilemap : public sf::Drawable, public sf::Transformable
    {
    public:
        /**
         * @brief Construct a new Tilemap object
         * 
         * @param width Size of the tilemap (in tiles)
         * @param tileSize Size of a (squared) tile in the tileset (in pixels)
         */
        Tilemap(const sf::Vector2i& mapSize, int tileSize);

        /**
         * @brief Build the vertex array from the tileset
         * @details Can be called multiple times to rebuild the tilemap without problems, but
         *          the map size, and the tile size shouldn't change.
         * 
         * @param tiles 
         */
        void build(const int* tiles);

        /**
         * @brief Use a new texture
         * @details Remove the old texture pointer without deleting it and replace it
         *          with the provided one.
         * 
         * @param newTexture 
         */
        void use(sf::Texture* newTexture);

        /**
         * @brief Update a tile in the vertex array
         * 
         * @param tilePos The position of the tile (in tiles) to update
         * @param new_tile New tile id for the tile
         */
        inline void update(const sf::Vector2i& tilePos, int new_tile);

    private:
        sf::Vector2i m_mapSize;
        int m_tileSize;
        sf::VertexArray m_vertices;
        sf::Texture* m_tileset;

        /**
         * @brief Function in charge of drawing our vertex array, using the SFML API
         * 
         * @param target 
         * @param states 
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#include "Tilemap.inl"

#endif