#include <Small/Scenes/Zone.hpp>

#include <cmath>

namespace sgl::Scenes
{
    Zone::Zone(int id, int tileSize, const sf::Vector2i& zoneSize, const sf::Vector2i& mapSize) :
        Scene(id), m_tileSize(tileSize), m_zoneSize(zoneSize), m_mapSize(mapSize),
        m_view(zoneSize / 2, zoneSize, tileSize), m_currentZone(0, 0), m_viewMovedByPx(0),
        m_lastQuantityNeededToStopTransition(0)
    {}

    sf::Vector2i Zone::getCurrentZone(const sf::Vector2f& pos, float dx, float dy)
    {
        return sf::Vector2i(
            std::lround(pos.x + dx) / (m_tileSize * m_zoneSize.x),
            std::lround(pos.y + dy) / (m_tileSize * m_zoneSize.y)
        );
    }

    bool Zone::isZoneValid(const sf::Vector2i& zone)
    {
        return !(zone.y < 0 || zone.x < 0 || zone.y >= m_mapSize.y || zone.x >= m_mapSize.x);
    }

    bool Zone::makeZoneTransition(const sf::Vector2f& pos, const sf::Time dt, int transitionSpeed)
    {
        sf::Vector2i newZone = getCurrentZone(pos);
        // move the view
        if (m_currentZone != newZone)
        {
            // direction
            sf::Vector2i diff = newZone - m_currentZone;
            // movement to do
            float dx = transitionSpeed * dt.asSeconds() * diff.x;
            float dy = transitionSpeed * dt.asSeconds() * diff.y;
            m_view.movePx(dx, dy);

            // update quantity to check when to stop the transition
            m_viewMovedByPx += static_cast<int>(std::abs(dx) + std::abs(dy));

            // calculate needed movement quantity to stop the transition only once
            // because we're doing a square root, and that is be costly
            if (m_lastQuantityNeededToStopTransition == 0)
            {
                int qx = diff.x * m_zoneSize.x * m_tileSize;
                int qy = diff.y * m_zoneSize.y * m_tileSize;
                m_lastQuantityNeededToStopTransition = static_cast<int>(std::sqrt(qx * qx + qy * qy));
            }

            // check if the transition is done or not
            if (m_viewMovedByPx >= m_lastQuantityNeededToStopTransition)
            {
                m_currentZone = newZone;
                // reset the position of the view to be sure we aren't a pixel off
                m_view.setCenter(newZone.x * m_tileSize + m_zoneSize.x / 2, newZone.y * m_tileSize + m_zoneSize.y / 2);
                // reset values
                m_viewMovedByPx = 0;
                m_lastQuantityNeededToStopTransition = 0;

                return false;  // the transition is considered done
            }
            return true;  // a transition is under progress
        }
        return false;  // no transition to do
    }
}