/**
 * @file Tilemap.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A tilemap wrapper, to render a lot of sprites in a single draw call
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_graphics_tilemap
#define sgl_graphics_tilemap

#include <SFML/Graphics.hpp>

namespace sgl::Graphics
{
    /**
     * @brief A tilemap wrapper
     * @details The texture is loaded and kept in the class
     * 
     */
    class Tilemap : public sf::Drawable, public sf::Transformable
    {
    public:
        /**
         * @brief Loading a tileset and building a vertex array
         * 
         * @param tileset Path to the tileset
         * @param tileSize Size of a single (squared) tile
         * @param tiles The indices of the tiles
         * @param width The width of the tilemap (in tiles)
         * @param height The height of the tilemap (in tiles)
         * @return true If the vertex array was successfully built
         * @return false If not
         */
        bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    private:
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

        /**
         * @brief Function in charge of drawing our vertex array, using the SFML API
         * 
         * @param target 
         * @param states 
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif