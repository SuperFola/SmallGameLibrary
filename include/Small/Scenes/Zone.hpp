/**
 * @file Zone.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief A specialized scene to handle zones and transitions on a tilemap
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef sgl_small_scenes_zones
#define sgl_small_scenes_zones

#include <Small/Core/Scene.hpp>
#include <Small/Graphics/TileView.hpp>

namespace sgl::Scenes
{
    /**
     * @brief A scene handling zones and transitions on a tilemap
     * @details Example of how to use:
     * @code
     * #include <cmath>
     * #include <Small/Scenes/Zone.hpp>
     * #include <Small/Graphics/Tilemap.hpp>
     * #include <Small/Graphics/TileView.hpp>
     * 
     * #include <SFML/Graphics.hpp>
     * #include <array>
     * 
     * class Bis : public sgl::Scenes::Zone
     * {
     * public:
     *     Bis(int id) :
     *         // tile size = 16, zone size = (8, 8), map size = (2, 1)
     *         sgl::Scenes::Zone(id, 16, sf::Vector2i(8, 8), sf::Vector2i(2, 1)),
     *         //   total map size (tiles)     tile size (px)
     *         m_tilemap(sf::Vector2i(16, 16), 16),
     *         m_playerShape(sf::Vector2f(16, 16)),
     *         m_canMove(true)
     *     {
     *         m_tileset.loadFromFile("assets/tileset.png");
     *         m_tilemap.use(&m_tileset);
     * 
     *        // build level
     *        m_level = {
     *            47,  46,  47,  35,  36,  36,  36,  37,  46,  45,  61,  47,  38,  42, 248,  39,
     *            63,  62,  63, 116, 116, 116, 116,  46,  45,  61,  45,  63,  38, 248,  43,  39,
     *            58,  58, 116,  16,  17,  17,  18,  62,  61,  45,  61,  47,  38, 248,  43,  39,
     *            33,  34, 116,  22, 241,  27,  23,  46,  45,  61,  45,  63,  38,  43,  43,  37,
     *            43,  43, 242,  19,  27,  27,  21,  62,  63,  62,  63,  32,  43,  42,  39,  46,
     *            42,  43,  34, 116,  19,  21, 116,  32,  33,  33,  33,  43, 248, 248,  39,  62,
     *            36,  43,  39,  58, 192, 192,  58,  35,  36,  36,  36,  36,  36,  43, 248,  34,
     *            58,  35,  37,  58,  58,  58,  58, 243,  58,  58,  58,  58,  58,  35,  36,  37
     *        };
     * 
     *        m_tilemap.build(m_level.data());
     *    }
     * 
     *    void onEvent(const sf::Event& event)
     *    {
     *        if (event.type == sf::Event::KeyPressed && m_canMove)
     *        {
     *            switch (event.key.code)
     *            {
     *            case sf::Keyboard::Z:
     *                if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 0, -16)))
     *                    m_playerShape.move(0, -16);
     *                break;
     * 
     *            case sf::Keyboard::Q:
     *                if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), -16, 0)))
     *                    m_playerShape.move(-16, 0);
     *                break;
     * 
     *            case sf::Keyboard::S:
     *                if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 0, 16)))
     *                    m_playerShape.move(0, 16);
     *                break;
     * 
     *            case sf::Keyboard::D:
     *                if (isZoneValid(getCurrentZone(m_playerShape.getPosition(), 16, 0)))
     *                    m_playerShape.move(16, 0);
     *                break;
     *            }
     *        }
     *    }
     * 
     *    void onUpdate(const sf::Time dt)
     *    {
     *        m_canMove = !makeZoneTransition(m_playerShape.getPosition(), dt, 5 * m_tileSize);
     *    }
     * 
     *    void onRender(sf::RenderTarget& screen)
     *    {
     *        m_view.use(screen);
     *        screen.draw(m_tilemap);
     *        screen.draw(m_playerShape);
     *    }
     * 
     * private:
     *     sf::Texture m_tileset;
     *     sgl::Graphics::Tilemap m_tilemap;
     * 
     *     sf::RectangleShape m_playerShape;
     *     bool m_canMove;
     * 
     *     std::array<int, 16 * 8> m_level;
     * };
     * @endcode
     * 
     */
    class Zone : public sgl::Scene
    {
    public:
        /**
         * @brief Construct a new Zone scene
         * 
         * @param id The identifier of the scene
         * @param tileSize The size of a (squared) tile, in pixels
         * @param zoneSize The size of a zone, in tiles
         * @param mapSize The size of the map, in zones
         */
        Zone(int id, int tileSize, const sf::Vector2i& zoneSize, const sf::Vector2i& mapSize);

    protected:
        const int m_tileSize;            ///< Size of a tile, in pixels
        const sf::Vector2i m_zoneSize;   ///< Size of a zone, in tiles
        const sf::Vector2i m_mapSize;    ///< Size of the map, in zones
        sgl::Graphics::TileView m_view;  ///< View for the map, handling transitions between zones
        sf::Vector2i m_currentZone;      ///< The zone in which the player is currently

        /**
         * @brief Get the current zone position in the map
         * 
         * @param pos The position of the entity to retrieve the zone of
         * @param dx x offset (0 by default)
         * @param dy y offset (0 by default)
         * @return sf::Vector2i Zone position
         */
        sf::Vector2i getCurrentZone(const sf::Vector2f& pos, float dx=0.f, float dy=0.f);

        /**
         * @brief Check if a zone is in map bounds
         * 
         * @param zone The position of the zone
         * @return true If the zone is reachable
         * @return false Otherwise
         */
        bool isZoneValid(const sf::Vector2i& zone);

        /**
         * @brief Check if a zone transition is needed, if so, move the view accordingly
         * @details This was designed to be called from the `onUpdate` Scene method
         * 
         * @param pos Position of the entity which should trigger the zone transition, should be the player
         * @param dt Delta of time since last update
         * @param transitionSpeed Speed of the transition, in pixels per second (default: 32 pix/sec)
         * @return true If a transition is under progress
         * @return false Otherwise
         */
        bool makeZoneTransition(const sf::Vector2f& pos, const sf::Time dt, int transitionSpeed=32);

    private:
        float m_viewMovedByPx;
        float m_lastQuantityNeededToStopTransition;
    };
}

#endif