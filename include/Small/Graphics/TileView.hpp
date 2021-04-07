/**
 * @file TileView.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Utility to build and manipulate views based on tiles
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_GRAPHICS_TILEVIEW_HPP
#define SMALL_GRAPHICS_TILEVIEW_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sgl::Graphics
{
    /**
     * @brief Wrapper around sf::View to manipule views using tiles coordinates
     * 
     */
    class TileView
    {
    public:
        /**
         * @brief Construct a new Tile View object
         * @details A default size for a tile is set to 16x16 pixels
         * 
         */
        TileView();

        /**
         * @brief Construct a new Tile View object
         * 
         * @param center The center of the view, in tiles
         * @param size The size of the view, in tiles
         * @param tileSize The size of a (squared) tile, in pixels
         */
        TileView(const sf::Vector2i& center, const sf::Vector2i& size, int tileSize);

        /**
         * @brief Activate the view
         * 
         * @param window 
         */
        void use(sf::RenderTarget& window);

        /**
         * @brief Set the size of a tile
         * @details Do not change the center or the size.
         * 
         * @param tileSize 
         */
        void setTileSize(int tileSize);

        /**
         * @brief Set the center of the view
         * 
         * @param x x coordinate, in tiles
         * @param y y coordinate, in tiles
         */
        void setCenter(unsigned x, unsigned y);

        /**
         * @brief Set the center of the view
         * 
         * @param x x coordinate, in pixels
         * @param y y coordinate, in pixels
         */
        void setCenterPx(float x, float y);

        /**
         * @brief Set the size of the view
         * 
         * @param width width in tiles
         * @param height height in tiles
         */
        void setSize(unsigned width, unsigned height);

        /**
         * @brief Set the size of the view
         * 
         * @param width width in tiles
         * @param height height in tiles
         */
        void setSizePx(float width, float height);

        /**
         * @brief Set the absolute orientation of the view
         * 
         * @param angle angle to rotate in degrees
         */
        void setRotation(float angle);

        /**
         * @brief Move the view
         * 
         * @param dx x offset in tiles
         * @param dy y offset in tiles
         */
        void move(unsigned dx, unsigned dy);

        /**
         * @brief Move the view
         * 
         * @param dx x offset in pixels
         * @param dy y offset in pixels
         */
        void movePx(float dx, float dy);

        /**
         * @brief Rotate the view relatively to its current orientation
         * 
         * @param angle angle to rotate in degrees
         */
        void rotate(float angle);

        /**
         * @brief Resize the view rectangle relatively to its current size
         * 
         * @param factor 
         */
        void zoom(float factor);

        /**
         * @brief Get the current orientation of the view
         * 
         * @return float 
         */
        float getRotation() const;

        /**
         * @brief Get the center of the view
         * 
         * @return sf::Vector2i center of the view in tiles
         */
        sf::Vector2i getCenter() const;

        /**
         * @brief Get the center of the view
         * 
         * @return const sf::Vector2f& center of the view in pixels
         */
        const sf::Vector2f& getCenterPx() const;

        /**
         * @brief Get the size of the view
         * 
         * @return sf::Vector2i size of the view in tiles
         */
        sf::Vector2i getSize() const;

        /**
         * @brief Get the sizee of the view
         * 
         * @return const sf::Vector2f& size of the view in pixels
         */
        const sf::Vector2f& getSizePx() const;

        /**
         * @brief Get the size of a tile
         * 
         * @return int 
         */
        int getTileSize() const;
    
    private:
        sf::View m_view;
        int m_tileSize;
    };
}

#endif
