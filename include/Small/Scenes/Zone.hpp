/**
 * @file ZoneScene.hpp
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
        const int m_tileSize;            //< Size of a tile, in pixels
        const sf::Vector2i m_zoneSize;   //< Size of a zone, in tiles
        const sf::Vector2i m_mapSize;    //< Size of the map, in zones
        sgl::Graphics::TileView m_view;  //< View for the map, handling transitions between zones
        sf::Vector2i m_currentZone;      //< The zone in which the player is currently

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
        int m_viewMovedByPx;
        int m_lastQuantityNeededToStopTransition;
    };
}

#endif