/**
 * @file Actor.hpp
 * @author Alexandre Plateau (lexplt.dev@gmail.com)
 * @brief Defines an actor class for your game, to represent a player or NPC for example
 * @version 0.1
 * @date 2020-05-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SMALL_GAMEOBJECTS_ACTOR_HPP
#define SMALL_GAMEOBJECTS_ACTOR_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Small/Graphics/Node.hpp>

namespace sgl::GameObjects
{
    /**
     * @brief A class to represent updatable, renderable and event receive entities
     * 
     */
    class Actor : public Graphics::Node
    {
    public:
        /**
         * @brief Construct a new Actor object
         * 
         */
        Actor();

        /**
         * @brief Destroy the Actor object
         * 
         */
        virtual ~Actor();

        /**
         * @brief Event handling method
         * 
         * @param event 
         */
        virtual void onEvent(const sf::Event& event);

        /**
         * @brief Scene updating method, called after having handled the events
         * 
         * @param dt 
         */
        virtual void onUpdate(const sf::Time dt);

        /**
         * @brief Rendering method of an object, to be implemented in subclasses
         * 
         * @param target Surface to render the object to
         * @param transform Parent transformation data
         */
        virtual void onRender(sf::RenderTarget& target, const sf::Transform& transform) = 0;

    protected:
    };
}

#endif
